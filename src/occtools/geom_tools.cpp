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

#include "geom_tools.h"

#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GCPnts_AbscissaPoint.hxx>

namespace occ {

/*! \class GeomTools
 *
 *  \ingroup occtools
 */

gp_Pnt GeomTools::geomCurveD0(const Handle_Geom_Curve& curve, Standard_Real u)
{
  gp_Pnt pnt;
  curve->D0(u, pnt);
  return pnt;
}

Standard_Real GeomTools::curveLength(const Handle_Geom_Curve& curve)
{
  if (!curve.IsNull()) {
    GeomAdaptor_Curve adaptor(curve);
    return GCPnts_AbscissaPoint::Length(adaptor);
  }
  return 0;
}

Standard_Real GeomTools::curveLengthBetweenParams(const Handle_Geom_Curve& curve,
                                                  Standard_Real firstU,
                                                  Standard_Real lastU)
{
  if (!curve.IsNull()) {
    GeomAdaptor_Curve adaptor(curve);
    return GCPnts_AbscissaPoint::Length(adaptor, firstU, lastU);
  }
  return 0;
}

gp_Vec GeomTools::normalToSurfaceAtUV(const Handle_Geom_Surface& surface,
                                      Standard_Real u,
                                      Standard_Real v)
{
  gp_Pnt point;
  gp_Vec d1u, d1v;
  surface->D1(u, v, point, d1u, d1v);
  return d1u ^ d1v;
}

} // namespace occ
