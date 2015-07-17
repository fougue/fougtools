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

#include "plugins_loader_instance_iface_filter.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QPluginLoader>

#include "../../cpptools/memory_utils.h"

namespace qtcore {
namespace internal {

void PluginsLoader_InstanceIFaceFilter_Helper::setRootComponentNullError(QString *error,
                                                                         const QPluginLoader *loader)
{
    cpp::checkedAssign(error, loader->errorString());
}

void PluginsLoader_InstanceIFaceFilter_Helper::setRootComponentIncompatibleError(QString *error,
                                                                                 const char *iid)
{
    cpp::checkedAssign(error, QCoreApplication::translate("qtcore::PluginsLoader",
                                                          "Root component has incompatible interface"
                                                          "(required: \"%1\"").arg(iid));
}

QObject *PluginsLoader_InstanceIFaceFilter_Helper::rootComponent(QPluginLoader *loader)
{
    return loader != NULL ? loader->instance() : NULL;
}

} // namespace internal
} // namespace qtcore
