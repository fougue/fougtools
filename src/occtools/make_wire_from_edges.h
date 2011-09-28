#ifndef OCC_MAKE_WIRE_FROM_EDGES_H
#define OCC_MAKE_WIRE_FROM_EDGES_H

#include "occtools/occtools.h"
#include <ShapeExtend_WireData.hxx>
#include <ShapeFix_Wire.hxx>
#include <TopoDS_Wire.hxx>
#include <algorithm>
#include <boost/bind.hpp>

namespace occ {

template<typename _FWD_ITERATOR_>
TopoDS_Wire makeWireFromEdges(_FWD_ITERATOR_ beginEdge, _FWD_ITERATOR_ endEdge)
{
  typedef void(ShapeExtend_WireData::* WireDataMemFun_t)(const TopoDS_Edge&,
                                                         const Standard_Integer);

  // Create a wire from the edges
  Handle_ShapeExtend_WireData wireData = new ShapeExtend_WireData;
  std::for_each(beginEdge, endEdge,
                boost::bind((WireDataMemFun_t)&ShapeExtend_WireData::Add,
                            wireData.operator->(), _1, 0));
  ShapeFix_Wire fixWire;
  fixWire.Load(wireData);
  fixWire.Perform();
  fixWire.FixReorder();
  fixWire.FixConnected();
  return fixWire.WireAPIMake();
}

} // namespace occ

#endif // OCC_MAKE_WIRE_FROM_EDGES_H
