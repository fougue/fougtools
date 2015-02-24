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

#include "point_on_faces_projector.h"

#include "math_utils.h"

#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <NCollection_UBTree.hxx>
#include <NCollection_UBTreeFiller.hxx>
#include <Poly_Triangulation.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>

#include <cmath>
#include <limits>
#include <map>

namespace occ {

//! TODO From OCC Forum :
//! try using DBRep_IsoBuilder to generate isolines representing your face.
//! Load the isolines into a DBRep_Face. Then, you can query the isolines to get
//! U and V parameters. Finally, use BRepAdaptor_Surface::Value to get the
//! actual points along the isolines.
//!
//! This could be used instead of the triangulation attached to each face.
//! More generally, face and "sample points" should be decoupled.
//! It should be up to the user to give sample points for each face.

namespace internal {

typedef std::pair<int, Handle_Poly_Triangulation> NodeIndexInTriangulation_t;
typedef NCollection_UBTree<NodeIndexInTriangulation_t, Bnd_Box> UBTreeOfNodeIndices_t;
typedef NCollection_UBTreeFiller<NodeIndexInTriangulation_t, Bnd_Box> UBTreeOfNodeIndicesFiller_t;

class NodeBndBoxSelector : public UBTreeOfNodeIndices_t::Selector
{
public:
    NodeBndBoxSelector(const gp_Pnt& pntToProject)
        : m_pntToProject(pntToProject),
          m_currMinDist(std::numeric_limits<double>::max()),
          m_currMinDistNodeId(-1, Handle_Poly_Triangulation())
    {
    }

    Standard_Boolean Reject(const Bnd_Box& bb) const
    {
        const bool result =
                bb.IsOpenXmin() == Standard_True
                || bb.IsOpenXmax() == Standard_True
                || bb.IsOpenYmin() == Standard_True
                || bb.IsOpenYmax() == Standard_True
                || bb.IsOpenZmin() == Standard_True
                || bb.IsOpenZmax() == Standard_True
                || bb.IsWhole() == Standard_True
                || bb.IsVoid() == Standard_True;
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
        const double dist = m_pntToProject.SquareDistance(pnt);
        if (dist < m_currMinDist || m_currMinDistNodeId.first == -1) {
            m_currMinDistNodeId = nodeId;
            m_currMinDist = dist;
            return Standard_True;
        }
        return Standard_False;
    }

    double minDistance() const
    {
        return std::sqrt(m_currMinDist);
    }

    const NodeIndexInTriangulation_t& minDistanceNodeIndex() const
    {
        return m_currMinDistNodeId;
    }

private:
    const gp_Pnt m_pntToProject;
    double m_currMinDist;
    NodeIndexInTriangulation_t m_currMinDistNodeId;
};

static const TopoDS_Face dummyFace;

} // namespace internal

class PointOnFacesProjector::Private
{
public:
    ~Private();

    void clear();

    const TopoDS_Face* triangulationToFace(Poly_Triangulation *tri) const;
    const TopoDS_Face* triangulationToFace(const Handle_Poly_Triangulation& tri) const;
    void insertMapping(const Handle_Poly_Triangulation& tri, const TopoDS_Face& face);

    std::map<const Poly_Triangulation*, TopoDS_Face> m_faceMap;
    internal::UBTreeOfNodeIndices_t m_ubTree;
};

PointOnFacesProjector::Private::~Private()
{
    this->clear();
}

void PointOnFacesProjector::Private::clear()
{
    m_faceMap.clear();
    m_ubTree.Clear();
}

const TopoDS_Face *PointOnFacesProjector::Private::triangulationToFace(Poly_Triangulation *tri) const
{
    auto it = m_faceMap.find(tri);
    return it != m_faceMap.end() ? &(it->second) : NULL;
}

const TopoDS_Face*
PointOnFacesProjector::Private::triangulationToFace(const Handle_Poly_Triangulation& tri) const
{
    return this->triangulationToFace(tri.operator->());
}

void PointOnFacesProjector::Private::insertMapping(const Handle_Poly_Triangulation &tri,
                                                   const TopoDS_Face &face)
{
    m_faceMap[tri.operator->()] = face;
}

/*! \class PointOnFacesProjector
 *  \brief Provides projection of a point on a soup of faces
 *
 *  \headerfile point_on_faces_projector.h <occtools/point_on_faces_projector.h>
 *  \ingroup occtools
 */

// --- PointOnFacesProjector::Result implementation

PointOnFacesProjector::Result::Result()
    : isValid(false),
      face(internal::dummyFace),
      point(occ::origin3d),
      normal(occ::zDir3d)
{
}

// --- PointOnFacesProjector implementation

PointOnFacesProjector::Result::Result(const TopoDS_Face& sFace,
                                      const gp_Pnt& sPoint,
                                      const gp_Vec& sNormal)
    : isValid(true),
      face(sFace),
      point(sPoint),
      normal(sNormal)
{
}

PointOnFacesProjector::PointOnFacesProjector()
    : d(new Private)
{
}

/*! \brief Construct a prepared projector (calling prepare(faces))
 *
 */
PointOnFacesProjector::PointOnFacesProjector(const TopoDS_Shape& faces)
    : d(new Private)
{
    this->prepare(faces);
}

PointOnFacesProjector::~PointOnFacesProjector()
{
    delete d;
}

void PointOnFacesProjector::prepare(const TopoDS_Shape& faces)
{
    d->clear();
    // Build the UB tree for binary search of points
    internal::UBTreeOfNodeIndicesFiller_t ubTreeFiller(d->m_ubTree, Standard_False);
    for (TopExp_Explorer exp(faces, TopAbs_FACE); exp.More(); exp.Next()) {
        const TopoDS_Face face = TopoDS::Face(exp.Current());
        if (!face.IsNull()) {
            TopLoc_Location loc;
            const Handle_Poly_Triangulation& triangulation = BRep_Tool::Triangulation(face, loc);
            if (!triangulation.IsNull()) {
                d->insertMapping(triangulation, face);
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
    // Find the closest node in the triangulations
    internal::NodeBndBoxSelector selector(point);
    if (d->m_ubTree.Select(selector) > 0) {
        const Handle_Poly_Triangulation& triangulation = selector.minDistanceNodeIndex().second;
        return d->triangulationToFace(triangulation);
    }
    return NULL;
}

PointOnFacesProjector::Result PointOnFacesProjector::projected(const gp_Pnt& point) const
{
    // Find the closest node in the triangulations
    internal::NodeBndBoxSelector selector(point);
    if (d->m_ubTree.Select(selector) <= 0)
        return PointOnFacesProjector::Result();

    const int minNodeId = selector.minDistanceNodeIndex().first;
    const Handle_Poly_Triangulation& triangulation = selector.minDistanceNodeIndex().second;

    // Find the triangle where distance is minimum
    const TColgp_Array1OfPnt& nodes = triangulation->Nodes();
    const Poly_Array1OfTriangle& triangles = triangulation->Triangles();
    double minDist = std::numeric_limits<double>::max();
    const Poly_Triangle* minTriangle = NULL;
    gp_Pnt projectedPnt;
    for (int iTri = triangles.Lower(); iTri <= triangles.Upper(); iTri++) {
        const Poly_Triangle& t = triangles(iTri);
        int n1, n2, n3;
        t.Get(n1, n2, n3);
        if (minNodeId == n1 || minNodeId == n2 || minNodeId == n3) {
            const auto projPntInfo =
                    MathUtils::projectPointOnTriangle(point, nodes(t(1)), nodes(t(2)), nodes(t(3)));
            const double dist = point.SquareDistance(projPntInfo.first);
            if (dist < minDist) {
                minTriangle = &t;
                minDist = dist;
                projectedPnt = projPntInfo.first;
            }
        }
    }

    if (minTriangle != NULL) {
        const TopoDS_Face* face = d->triangulationToFace(triangulation);
        const TopAbs_Orientation faceOrientation = face != NULL ? face->Orientation() : TopAbs_FORWARD;
        const gp_Vec triNormal = occ::MathUtils::triangleNormal(nodes, *minTriangle, faceOrientation);
        return PointOnFacesProjector::Result(face != NULL ? *face : TopoDS_Face(),
                                             projectedPnt,
                                             triNormal);
    }
    return PointOnFacesProjector::Result();
}

/*! \brief Syntactic sugar around projected()
 */
PointOnFacesProjector::Result PointOnFacesProjector::operator()(const gp_Pnt& point) const
{
    return this->projected(point);
}

} // namespace occ
