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

#include "qt_occ.h"

namespace occ {

//! Conversion of the Quantity_Color \p c to a QColor
QColor toQtColor(const Quantity_Color& c)
{
  return QColor(c.Red() * 255., c.Green() * 255., c.Blue() * 255.);
}

//! Conversion of the Quantity_NameOfColor \p c to a QColor
QColor toQtColor(const Quantity_NameOfColor c)
{
  Quantity_Color qc(c);
  return toQtColor(qc);
}

//! Conversion of the QColor \p c to a Quantity_Color
Quantity_Color toOccColor(const QColor& c)
{
  return Quantity_Color(c.red() / 255., c.green() / 255., c.blue() / 255., Quantity_TOC_RGB);
}

//! Conversion of the QColor object \p c to a Quantity_NameOfColor
Quantity_NameOfColor toNamedOccColor(const QColor& c)
{
  return toOccColor(c).Name();
}

//! Conversion of the QString \p str to an OCC CString
Standard_CString toCString(const QString& str)
{
  return str.toLocal8Bit().constData();
}

//! Conversion of the QString \p str to an OCC TCollection_AsciiString
TCollection_AsciiString toAsciiString(const QString& str)
{
  return TCollection_AsciiString(toCString(str));
}

//! Conversion of the QString \p str to an OCC ExtString
Standard_ExtString toExtString(const QString& str)
{
  return reinterpret_cast<Standard_ExtString>(str.utf16());
}

//! Conversion of the QString \p str to an OCC TCollection_ExtendedString
TCollection_ExtendedString toOccExtendedString(const QString& str)
{
  return TCollection_ExtendedString(toExtString(str));
}

//! Conversion of the OCC TCollection_AsciiString \p str to a QString
QString toQString(const TCollection_AsciiString& str)
{
  return QString::fromLatin1(str.ToCString(), str.Length());
}

//! Conversion of the OCC TCollection_ExtendedString \p str to a QString
QString toQString(const TCollection_ExtendedString& str)
{
  return QString::fromUtf16(reinterpret_cast<const ushort*>(str.ToExtString()), str.Length());
}

} // namespace occ
