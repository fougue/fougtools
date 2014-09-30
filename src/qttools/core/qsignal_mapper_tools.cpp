/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
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

#include "qsignal_mapper_tools.h"

namespace qttools {

/*!
 * \class QSignalMapperTools
 * \brief Provides a collection of tools around QSignalMapper
 * \headerfile qsignal_mapper_tools.h <qttools/core/qsignal_mapper_tools.h>
 * \ingroup qttools_core
 */

/*! \brief Returns the member function pointer(Qt signal) to QSignalMapper::mapped(int)
 *
 *  This is a helper to disambiguate and choose the right QSignalMapper::mapped() signal overload.
 *  It is particularly useful for the new Qt5 QObject::connect() syntax. \n
 *  Example :
 *  \code
 *      // Error: the compiler doesn't know the right QSignalMapper::mapped() overload to pick
 *      QObject::connect(sigMap, &QSignalMapper::mapped, this, &MyClass:onSigMapped);
 *
 *      // You have to specify the signal overload :
 *      QObject::connect(sigMap, (void QSignalMapper::*(int))&QSignalMapper::mapped,
 *                       this, &MyClass:onSigMapped);
 *
 *      // More readable :
 *      QObject::connect(sigMap, qttools::QSignalMapperTools::signalMapped_int(),
 *                       this, &MyClass:onSigMapped);
 *  \endcode
 *
 */
QSignalMapperTools::SignalMapped_int QSignalMapperTools::signalMapped_int()
{
    return (QSignalMapperTools::SignalMapped_int)&QSignalMapper::mapped;
}

/*! \brief Returns the member function pointer(Qt signal) to QSignalMapper::mapped(const QString&)
 *  \sa QSignalMapperTools::signalMapped_int()
 */
QSignalMapperTools::SignalMapped_QString QSignalMapperTools::signalMapped_QString()
{
    return (QSignalMapperTools::SignalMapped_QString)&QSignalMapper::mapped;
}

/*! \brief Returns the member function pointer(Qt signal) to QSignalMapper::mapped(QWidget*)
 *  \sa QSignalMapperTools::signalMapped_int()
 */
QSignalMapperTools::SignalMapped_QWidgetPtr QSignalMapperTools::signalMapped_QWidgetPtr()
{
    return (QSignalMapperTools::SignalMapped_QWidgetPtr)&QSignalMapper::mapped;
}

/*! \brief Returns the member function pointer(Qt signal) to QSignalMapper::mapped(QObject*)
 *  \sa QSignalMapperTools::signalMapped_int()
 */
QSignalMapperTools::SignalMapped_QObjectPtr QSignalMapperTools::signalMapped_QObjectPtr()
{
    return (QSignalMapperTools::SignalMapped_QObjectPtr)&QSignalMapper::mapped;
}

/*! \brief Returns the member function pointer(Qt slot) to QSignalMapper::map()
 *
 *  This is a helper to disambiguate and choose the right QSignalMapper::map() slot overload.
 *  It is particularly useful for the new Qt5 QObject::connect() syntax. \n
 *  Example :
 *  \code
 *      // Error: the compiler doesn't know the right QSignalMapper::map() overload to pick
 *      QObject::connect(action, &QAction::triggered, sigMap, &QSignalMapper::map);
 *
 *      // You have to specify the slot overload :
 *      QObject::connect(action, &QAction::triggered,
 *                       sigMap, (void QSignalMapper::*())&QSignalMapper::map);
 *
 *      // More readable :
 *      QObject::connect(action, &QAction::triggered,
 *                       sigMap, qttools::QSignalMapperTools::slotMap());
 *  \endcode
 */
QSignalMapperTools::SlotMap QSignalMapperTools::slotMap()
{
    return (QSignalMapperTools::SlotMap)&QSignalMapper::map;
}

/*! \brief Returns the member function pointer(Qt slot) to QSignalMapper::map(QObject*)
 *  \sa QSignalMapperTools::slotMap()
 */
QSignalMapperTools::SlotMap_QObjectPtr QSignalMapperTools::slotMap_QObjectPtr()
{
    return (QSignalMapperTools::SlotMap_QObjectPtr)&QSignalMapper::map;
}

} // namespace qttools
