/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
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
    static void setRootComponentNullError(
            QString* error, const QPluginLoader* loader);
    static void setRootComponentIncompatibleError(
            QString* error, const char* iid);
    static QObject* rootComponent(QPluginLoader* loader);
};

} // namespace internal

/*! \brief Generic plugin filter that keeps only root components satisfying an interface
 *
 *  \tparam INTERFACE Type of the interface (declared with Q_DECLARE_INTERFACE())
 *  \headerfile plugins_loader_instance_iface_filter.h
 *              <qttools/core/plugins_loader_instance_iface_filter.h>
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
            if (qobject_cast<INTERFACE*>(rootComponent(loader)) != NULL) {
                return true;
            }
            else {
                setRootComponentIncompatibleError(
                            error, qobject_interface_iid<INTERFACE>());
            }
        }
        else {
            setRootComponentNullError(error, loader);
        }
        return false;
    }
};

} // namespace qtcore
