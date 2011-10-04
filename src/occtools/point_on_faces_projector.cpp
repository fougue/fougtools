/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language, the Qt and Open Cascade toolkits.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "occtools/point_on_faces_projector.h"

#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <NCollection_UBTree.hxx>
#include <NCollection_UBTreeFiller.hxx>
#include <Poly_Triangulation.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>
#include <limits>
#include "mathtools/project_point_on_triangle.h"
#include "occtools/pnt_vec_traits.h"
#include "occtools/utils.h"

//! TODO From OCC Forum :
//! try using DBRep_IsoBuilder to generate isolines representing your face.
//! Load the isolines into a DBRep_Face. Then, you can query the isolines to get
//! U and V parameters. Finally, use BRepAdaptor_Surface::Value to get the
//! actual points along the isolines.
//!
//! This could be used instead of the triangulation attached to each face.
//! More generally, face and "sample points" should be decoupled.
//! It should be up to the user to give sample points for each face.

namespace {

typedef std::pair<int, Handle_Poly_Triangulation>
NodeIndexInTriangulation_t;
typedef NCollection_UBTree<NodeIndexInTriangulation_t, Bnd_Box>
UBTreeOfNodeIndices_t;
typedef NCollection_UBTreeFiller<NodeIndexInTriangulation_t, Bnd_Box>
UBTreeOfNodeIndicesFiller_t;

class NodeBndBoxSelector : public UBTreeOfNodeIndices_t::Selector
{
public:
  NodeBndBoxSelector(const gp_Pnt& pntToProject) :
    _pntToProject(pntToProject),
    _currMinDist(std::numeric_limits<double>::max()),
    _currMinDistNodeId(-1, Handle_Poly_Triangulation())
  {
  }

  Standard_Boolean Reject(const Bnd_Box& bb) const
  {
    const bool result = bb.IsOpenXmin() == Standard_True ||
        bb.IsOpenXmax() == Standard_True ||
        bb.IsOpenYmin() == Standard_True ||
        bb.IsOpenYmax() == Standard_True ||
        bb.IsOpenZmin() == Standard_True ||
        bb.IsOpenZmax() == Standard_True ||
        bb.IsWhole() == Standard_True ||
        bb.IsVoid() == Standard_True;
    return result ? Standard_True : Standard_False;
  }

  Standard_Boolean Accept(const NodeIndexInTriangulation_t& nodeId)
  {
    if (nodeId.second.IsNull())
      return Standard_False;
    const TColgp_Array1OfPnt& nodes = nodeId.second->Nodes();
    if (!(nodes.Lower() <= nodeId.first && nodeId.first <= nodes.Upper()))
      return Standard_False;
    const gp_Pnt& pnt = nodes(nodeId.first);
    const double dist = _pntToProject.SquareDistance(pnt);
    if (dist < _currMinDist || _currMinDistNodeId.first == -1) {
      _currMinDistNodeId = nodeId;
      _currMinDist = dist;
      return Standard_True;
    }
    return Standard_False;
  }

  double minDistance() const
  {
    return std::sqrt(_currMinDist);
  }

  const NodeIndexInTriangulation_t& minDistanceNodeIndex() const
  {
    return _currMinDistNodeId;
  }

private:
  const gp_Pnt _pntToProject;
  double _currMinDist;
  NodeIndexInTriangulation_t _currMinDistNodeId;
};

} // Anonymous namespace

namespace occ {

class PointOnFacesProjectorPrivate
{
public:
  ~PointOnFacesProjectorPrivate()
  {
    this->clear();
  }

  void clear()
  {
    this->faceMap.clear();
    this->ubTree.Clear();
  }

  boost::unordered_map<Poly_Triangulation*, TopoDS_Face> faceMap;
  UBTreeOfNodeIndices_t ubTree;
};

// --- PointOnFacesProjector::Result implementation

PointOnFacesProjector::Result::Result() :
  isValid(false),
  face(TopoDS_Face()),
  point(occ::origin3d),
  normal(occ::zDir3d)
{
}

// --- PointOnFacesProjector implementation

PointOnFacesProjector::Result::Result(const TopoDS_Face& sFace,
                                      const gp_Pnt& sPoint,
                                      const gp_Vec& sNormal) :
  isValid(true),
  face(sFace),
  point(sPoint),
  normal(sNormal)
{
}

PointOnFacesProjector::PointOnFacesProjector() :
  _d(new PointOnFacesProjectorPrivate)
{
}

/*! \brief Construct a prepared projector (calling prepare(faces))
 *
 */
PointOnFacesProjector::PointOnFacesProjector(const TopoDS_Shape& faces) :
  _d(new PointOnFacesProjectorPrivate)
{
  this->prepare(faces);
}

PointOnFacesProjector::~PointOnFacesProjector()
{
  delete _d;
}

void PointOnFacesProjector::prepare(const TopoDS_Shape& faces)
{
  _d->clear();
  // Build the UB tree for binary search of points.
  UBTreeOfNodeIndicesFiller_t ubTreeFiller(_d->ubTree, Standard_False);
  for (TopExp_Explorer exp(faces, TopAbs_FACE); exp.More(); exp.Next()) {
    const TopoDS_Face face = TopoDS::Face(exp.Current());
    if (!face.IsNull()) {
      TopLoc_Location loc;
      const Handle_Poly_Triangulation& triangulation = BRep_Tool::Triangulation(face, loc);
      if (!triangulation.IsNull()) {
        _d->faceMap[triangulation.operator->()] = face;
        const gp_Trsf& trsf = loc.Transformation();
        const TColgp_Array1OfPnt& nodes = triangulation->Nodes();
        for (int i = nodes.Lower(); i <= nodes.Upper(); ++i) {
          const gp_Pnt iNode(nodes(i).Transformed(trsf));
          Bnd_Box ibb;
          ibb.Set(iNode);
          ubTreeFiller.Add(std::make_pair(i, triangulation), ibb);
        }
      }
    }
  }
  ubTreeFiller.Fill();
}

const TopoDS_Face* PointOnFacesProjector::faceOfProjection(const gp_Pnt& point) const
{
  // Find the closest node in the triangulations.
  NodeBndBoxSelector selector(point);
  if (_d->ubTree.Select(selector) <= 0)
    return 0;
  const Handle_Poly_Triangulation& triangulation =
      selector.minDistanceNodeIndex().second;
  return &(_d->faceMap[triangulation.operator->()]);
}

PointOnFacesProjector::Result PointOnFacesProjector::projected(const gp_Pnt& point) const
{
  // Find the closest node in the triangulations.
  NodeBndBoxSelector selector(point);
  if (_d->ubTree.Select(selector) <= 0)
    return PointOnFacesProjector::Result();

  const int minNodeId = selector.minDistanceNodeIndex().first;
  const Handle_Poly_Triangulation& triangulation =
      selector.minDistanceNodeIndex().second;
  // Find the triangle where distance is minimum.
  const TColgp_Array1OfPnt& nodes = triangulation->Nodes();
  const Poly_Array1OfTriangle& triangles = triangulation->Triangles();
  double minDist = std::numeric_limits<double>::max();
  const Poly_Triangle* minTriangle = 0;
  gp_Pnt projectedPnt;
  for (int iTri = triangles.Lower(); iTri <= triangles.Upper(); iTri++) {
    const Poly_Triangle& t = triangles(iTri);
    int n1, n2, n3;
    t.Get(n1, n2, n3);
    if (minNodeId == n1 || minNodeId == n2 || minNodeId == n3) {
      const std::pair<gp_Pnt, bool> projPntInfo =
          geom::projectPointOnTriangle<occ::PntVecTraits_t>(
            point, nodes(t(1)), nodes(t(2)), nodes(t(3)));
      const double dist = point.SquareDistance(projPntInfo.first);
      if (dist < minDist) {
        minTriangle = &t;
        minDist = dist;
        projectedPnt = projPntInfo.first;
      }
    }
  }
  if (minTriangle == 0)
    return PointOnFacesProjector::Result();
  const TopoDS_Face& face = _d->faceMap[triangulation.operator->()];
  return PointOnFacesProjector::Result(face, projectedPnt,
                                       occ::triangleNormal(nodes, *minTriangle, face.Orientation()));
}

/*! \brief Syntactic sugar around projected()
 */
PointOnFacesProjector::Result PointOnFacesProjector::operator()(const gp_Pnt& point) const
{
  return this->projected(point);
}

} // namespace occ
