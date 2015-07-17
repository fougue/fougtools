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

#include "plugins_loader_instance_filter.h"
#include <QtCore/QPluginLoader>

namespace qtcore {

/*! \class PluginsLoader_InstanceFilter
 *  \brief Provides plugin filter to be used with PluginsLoader
 *
 *  This class is considered as an inner class of PluginsLoader
 *
 *  \headerfile plugins_loader.h <qttools/core/plugins_loader.h>
 *  \ingroup qttools_core
 */

/*! \brief Keep or discard the root component of QPluginLoader \p loader
 *
 *  Sub-classes can require access to the root component, other can avoid
 *  loading by using QPluginLoader::metaData()
 *
 *  By default this functions does nothing apart checking \p loader is non null.
 *
 *  \param[in,out] loader The plugin loader providing the root component. The
 *                 root component is not loaded, the filter might load it with
 *                 QPluginLoader::instance()
 *  \param[out] error Used to report error in case the root component is
 *              filtered out
 *
 *  \return Returns true is the root component can be kept
 */
bool PluginsLoader_InstanceFilter::accepts(
        QPluginLoader *loader, QString* /*error*/) const
{
    return loader != NULL;
}

} // namespace qtcore
