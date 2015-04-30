/****************************************************************************
**
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
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

#pragma once

#include "occtools.h"

#include <Quantity_Color.hxx>
#include <Quantity_NameOfColor.hxx>
#include <TCollection_AsciiString.hxx>
#include <TCollection_ExtendedString.hxx>

#include <QtCore/QString>
#include <QtGui/QColor>

namespace occ {

class OCCTOOLS_EXPORT QtUtils
{
public:
    // --- Color conversion

    static QColor toQColor(const Quantity_Color& c);
    static QColor toQColor(const Quantity_NameOfColor c);
    static Quantity_Color toOccColor(const QColor& c);
    static Quantity_NameOfColor toOccNameOfColor(const QColor& c);

    // --- String conversion

    static TCollection_AsciiString toOccLatin1String(const QString& str);
    static TCollection_AsciiString toOccLocal8BitString(const QString& str);
    static TCollection_AsciiString toOccUtf8String(const QString& str);
    static Standard_ExtString toOccExtString(const QString& str);
    static TCollection_ExtendedString toOccExtendedString(const QString& str);

    static QString fromLatin1ToQString(const TCollection_AsciiString& str);
    static QString fromLocal8BitToQString(const TCollection_AsciiString& str);
    static QString fromUtf8ToQString(const TCollection_AsciiString& str);
    static QString toQString(Standard_ExtString unicodeStr, int size = -1);
    static QString toQString(const TCollection_ExtendedString& str);

    // TODO: add conversion for NCollection_String.hxx

    template<typename OCC_PNT_VEC>
    static QString toQString(const OCC_PNT_VEC& pv,
                             const QString& format = QLatin1String("(%x, %y, %z)"),
                             char realFormat = 'g',
                             unsigned prec = 6);
};

//
// --- Implementation
//

template<typename OCC_PNT_VEC>
QString QtUtils::toQString(
        const OCC_PNT_VEC& pv, const QString& format, char realFormat, unsigned prec)
{
    QString result = format;
    result.replace(QLatin1String("%x"), QString::number(pv.X(), realFormat, prec));
    result.replace(QLatin1String("%y"), QString::number(pv.Y(), realFormat, prec));
    return result.replace(QLatin1String("%z"), QString::number(pv.Z(), realFormat, prec));
}

} // namespace occ
