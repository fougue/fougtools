/****************************************************************************
**
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
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

#pragma once

#include "plugins_loader_instance_filter.h"

#include <QtCore/QObject>

namespace qtcore {

namespace internal {

/*! \brief Helper class for PluginsLoader_InstanceIFaceFilter only
 *  \ingroup qttools_core
 */
class QTTOOLS_CORE_EXPORT PluginsLoader_InstanceIFaceFilter_Helper
{
protected:
    static void setRootComponentNullError(QString* error, const QPluginLoader* loader);
    static void setRootComponentIncompatibleError(QString* error, const char* iid);
    static QObject* rootComponent(QPluginLoader* loader);
};

} // namespace internal

/*! \brief Generic plugin filter that keeps only root components satisfying an interface
 *
 *  \tparam INTERFACE Type of the interface (declared with Q_DECLARE_INTERFACE())
 *  \headerfile plugins_loader_instance_iface_filter.h <qttools/core/plugins_loader_instance_iface_filter.h>
 *  \ingroup qttools_core
 */
template<typename INTERFACE>
class PluginsLoader_InstanceIFaceFilter :
        public PluginsLoader_InstanceFilter,
        protected internal::PluginsLoader_InstanceIFaceFilter_Helper
{
public:
    bool accepts(QPluginLoader *loader, QString* error = NULL) const
    {
        if (rootComponent(loader) != NULL) {
            if (qobject_cast<INTERFACE*>(rootComponent(loader)) != NULL)
                return true;
            else
                setRootComponentIncompatibleError(error, qobject_interface_iid<INTERFACE>());
        }
        else {
            setRootComponentNullError(error, loader);
        }
        return false;
    }
};

} // namespace qtcore
