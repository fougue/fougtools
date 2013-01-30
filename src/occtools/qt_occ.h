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

#ifndef OCC_QT_OCC_H
#define OCC_QT_OCC_H

#include "occtools.h"

#include <Quantity_Color.hxx>
#include <Quantity_NameOfColor.hxx>
#include <TCollection_AsciiString.hxx>
#include <TCollection_ExtendedString.hxx>

#include <QtCore/QString>
#include <QtGui/QColor>

namespace occ {

// --- Color conversion

OCCTOOLS_EXPORT QColor toQtColor(const Quantity_Color& c);
OCCTOOLS_EXPORT QColor toQtColor(const Quantity_NameOfColor c);
OCCTOOLS_EXPORT Quantity_Color toOccColor(const QColor& c);
OCCTOOLS_EXPORT Quantity_NameOfColor toNamedOccColor(const QColor& c);

// --- String conversion

OCCTOOLS_EXPORT Standard_CString toCString(const QString& str);
OCCTOOLS_EXPORT TCollection_AsciiString toAsciiString(const QString& str);
OCCTOOLS_EXPORT Standard_ExtString toExtString(const QString& str);
OCCTOOLS_EXPORT TCollection_ExtendedString toOccExtendedString(const QString& str);

template<typename OCC_PNT_VEC>
QString toString(const OCC_PNT_VEC& pv,
                 const QString& format = QLatin1String("(%x, %y, %z)"),
                 char realFormat = 'g', unsigned prec = 6);



//
// Implementation
//

template<typename OCC_PNT_VEC>
QString toString(const OCC_PNT_VEC& pv,
                 const QString& format,
                 char realFormat, unsigned prec)
{
  QString result = format;
  result.replace("%x", QString::number(pv.X(), realFormat, prec));
  result.replace("%y", QString::number(pv.Y(), realFormat, prec));
  return result.replace("%z", QString::number(pv.Z(), realFormat, prec));
}

} // namespace occ

#endif // OCC_QT_OCC_H
