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

#include "plugins_loader_instance_filter.h"
#include <QtCore/QPluginLoader>

namespace qttools {

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
 *  Sub-classes can require access to the root component, other can avoid loading by using
 *  QPluginLoader::metaData()
 *
 *  By default this functions does nothing apart checking \p loader is non null.
 *
 *  \param[in,out] loader The plugin loader providing the root component. The root component is not
 *                        loaded, the filter might load it with QPluginLoader::instance()
 *  \param[out] error Used to report error in case the root component is filtered out
 *
 *  \return Returns true is the root component can be kept
 */
bool PluginsLoader_InstanceFilter::accepts(QPluginLoader *loader, QString *error) const
{
    Q_UNUSED(error);
    return loader != NULL;
}

} // namespace qttools
