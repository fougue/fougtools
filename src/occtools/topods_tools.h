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

#ifndef OCC_TOPODS_TOOLS_H
#define OCC_TOPODS_TOOLS_H

#include "occtools.h"

#include <BRep_Builder.hxx>
#include <Handle_ShapeExtend_WireData.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Vec.hxx>

#include <string>

namespace occ {

class OCCTOOLS_EXPORT TopoDsTools
{
public:
  template<typename FWD_ITERATOR>
  static TopoDS_Compound makeCompound(FWD_ITERATOR iBegin, FWD_ITERATOR iEnd);

  template<typename CONTAINER>
  static TopoDS_Compound makeCompound(CONTAINER cnter);

  template<typename FWD_ITERATOR>
  static TopoDS_Wire makeWireFromEdgeRange(FWD_ITERATOR beginEdge, FWD_ITERATOR endEdge);

  static gp_Vec normalToFaceAtUV(const TopoDS_Face& face, Standard_Real u, Standard_Real v);

  static std::string shapeToString(const TopoDS_Shape& shape);
  static TopoDS_Shape shapeFromString(const std::string& str);

private:
  static Handle_ShapeExtend_WireData createShapeExtendWireData();
  static void addEdge(const Handle_ShapeExtend_WireData& wireData, const TopoDS_Edge& edge);
  static TopoDS_Wire fixedWire(const Handle_ShapeExtend_WireData& wireData);
};



// --
// -- Implementation
// --

//! Topologic compound of shapes denoted between the begin and end iterators \p iBegin and \p iEnd
template<typename FWD_ITERATOR>
TopoDS_Compound TopoDsTools::makeCompound(FWD_ITERATOR iBegin, FWD_ITERATOR iEnd)
{
  TopoDS_Compound cmpd;
  BRep_Builder builder;
  builder.MakeCompound(cmpd);

  while (iBegin != iEnd) {
    builder.Add(cmpd, *iBegin);
    ++iBegin;
  }

  return cmpd;
}

//! Shorthand to occ::makeCompound(cnter.begin(), cnter.end())
template<typename CONTAINER>
TopoDS_Compound TopoDsTools::makeCompound(CONTAINER cnter)
{
  return TopoDsTools::makeCompound(cnter.begin(), cnter.end());
}

template<typename FWD_ITERATOR>
TopoDS_Wire TopoDsTools::makeWireFromEdgeRange(FWD_ITERATOR beginEdge, FWD_ITERATOR endEdge)
{
  Handle_ShapeExtend_WireData wireData = TopoDsTools::createShapeExtendWireData();
  while (beginEdge != endEdge) {
    TopoDsTools::addEdge(wireData, *beginEdge);
    ++beginEdge;
  }
  return TopoDsTools::fixedWire(wireData);
}

} // namespace occ

#endif // OCC_TOPODS_TOOLS_H
