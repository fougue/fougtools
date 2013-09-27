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

#include "abstract_plugin_loader.h"

#include <QtCore/QDir>
#include <QtCore/QHash>
#include <QtCore/QLibrary>
#include <QtCore/QPluginLoader>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>

#include <QtCore/QtDebug>

namespace qttools {

namespace internal {

static bool isLibrary(const QString& path)
{
  return path.endsWith(QLatin1String(".so")) || path.endsWith(QLatin1String(".dll"));
}

} // namespace internal

/*! \class AbstractPluginLoaderPrivate
 *  \brief Internal (pimpl of AbstractPluginLoader)
 */
class AbstractPluginLoader::Private
{
public:
  Private()
    : m_autoDeletePlugins(true)
  {
    m_plugins.reserve(100);
    m_pluginLoaders.reserve(100);
  }

  QVector<QObject*> m_plugins;
  QVector<QPluginLoader*> m_pluginLoaders;
  QHash<const QObject*, QString> m_pluginFilenames;
  bool m_autoDeletePlugins;
  QString m_loadingFolder;
};

/*!
 * \class AbstractPluginLoader
 * \brief Base abstract class for dynamic loading of plugins

 * \headerfile abstract_plugin_loader.h <qttools/core/abstract_plugin_loader.h>
 * \ingroup qttools_core
 *
 * AbstractPluginLoader loads plugin DLLs from a specified folder (see setLoadingFolder() and
 * loadPlugins()).
 *
 * AbstractPluginLoader cannot be used as is, function isPluginCompatible() must be redefined.
 */

AbstractPluginLoader::AbstractPluginLoader()
  : d(new Private)
{
}

AbstractPluginLoader::~AbstractPluginLoader()
{
  foreach (QPluginLoader* pluginLoader, d->m_pluginLoaders) {
    if (pluginLoader != NULL) {
      if (this->autoDeletePlugins())
        pluginLoader->unload();
      delete pluginLoader;
    }
  }
  delete d;
}

/*!
 * \brief Is auto-deletion of plugins enabled ?
 *
 * If plugins auto-deletion is enabled, AbstractPluginLoader will automatically delete plugins
 * (and the associated QPluginLoader) on destruction of this object.
 *
 * \sa setAutoDeletePlugins()
 */
bool AbstractPluginLoader::autoDeletePlugins() const
{
  return d->m_autoDeletePlugins;
}

/*!
 * \brief Enables plugins auto-deletion of \p on is true; otherwise auto-deletion is disabled
 * \sa autoDeletePlugins()
 */
void AbstractPluginLoader::setAutoDeletePlugins(bool on)
{
  d->m_autoDeletePlugins = on;
}

/*!
 * \brief The folder used when dynamically loading plugins
 * \sa setLoadingFolder()
 */
QString AbstractPluginLoader::loadingFolder() const
{
  return d->m_loadingFolder;
}

/*!
 * \brief Set the folder used when dynamically loading plugins
 * \sa loadingFolder()
 */
void AbstractPluginLoader::setLoadingFolder(const QString& folder)
{
  d->m_loadingFolder = folder;
}

/*!
 * \brief File name of a loaded plugin object (e.g. libmy_plugin.so, other_plugin.dll, ...)
 *
 *  \p plugin must have been successfully loaded with loadPlugins()
 */
QString AbstractPluginLoader::filename(const QObject* plugin) const
{
  if (d->m_pluginFilenames.contains(plugin))
    return d->m_pluginFilenames.value(plugin);
  return QString();
}

/*!
 * \brief Array of all loaded plugin objects
 */
QVector<QObject*> AbstractPluginLoader::plugins()
{
  return d->m_plugins;
}

/*!
 * \brief Read-only array of all loaded plugin objects
 */
const QVector<QObject*>& AbstractPluginLoader::plugins() const
{
  return d->m_plugins;
}

/*!
 * \brief Load plugins with file names matchine regexp \p fileRx, any error is reported in \p errors
 */
void AbstractPluginLoader::loadPlugins(const QRegExp& fileRx, QVector<QString>* errors)
{
  const QDir pluginsFolder(this->loadingFolder());
  QStringList entries(pluginsFolder.entryList(QDir::Files));
  foreach (const QString& entry, entries) {
    if (fileRx.indexIn(entry) != -1 && internal::isLibrary(entry)) {
      // Try to load the plugin
#ifdef DEBUG_ABSTRACT_PLUGIN_LOADER
      qDebug() << "try to load" << entry;
#endif // DEBUG_ABSTRACT_PLUGIN_LOADER
      QPluginLoader* pluginLoader = new QPluginLoader(pluginsFolder.absoluteFilePath(entry));
      QObject* plugin = pluginLoader->instance();
      // Is the plugin compatible ?
      if (this->isPluginCompatible(plugin)) {
        d->m_plugins.append(plugin);
        d->m_pluginLoaders.append(pluginLoader);
        d->m_pluginFilenames.insert(plugin, entry);
      }
      else {
#ifdef DEBUG_ABSTRACT_PLUGIN_LOADER
        qDebug() << "  not added";
#endif // DEBUG_ABSTRACT_PLUGIN_LOADER
        if (errors != NULL) {
          //: %1 holds the path to a plugin (DLL)
          //: %2 holds an error description
          errors->append(QObject::tr("Failed to load plugin (maybe wrong interface) %1 : %2")
                         .arg(pluginLoader->fileName())
                         .arg(pluginLoader->errorString()));
        }
        pluginLoader->unload();
        delete pluginLoader;
      } // end if (this->isPluginCompatible(plugin))
    } // end if (fileRx.indexIn(entry) != -1)
  } // end foreach ()
}

/*! \brief Remove a previously loaded plugin object
 */
void AbstractPluginLoader::discardPlugin(QObject* plugin)
{
  for (int i = 0; i < d->m_plugins.size(); ++i) {
    if (plugin == d->m_plugins.at(i)) {
      d->m_plugins.remove(i);
      if (this->autoDeletePlugins())
        d->m_pluginLoaders.at(i)->unload();
      delete d->m_pluginLoaders.at(i);
      d->m_pluginLoaders.remove(i);
    }
  }
  d->m_pluginFilenames.remove(plugin);
}

/*!
 *  \fn bool AbstractPluginLoader::isPluginCompatible(const QObject*) const
 *  \brief Check if a not yet added (but loaded) plugin object is compatible with this plugin
 *         loader
 *
 *  This abstract function acts like a filter when loading plugins. It is called by loadPlugins()
 *  any time a new plugin object has just been loaded. If isPluginCompatible() returns false then
 *  the new plugin is destroyed and not added to the array of available plugins (see plugins())
 */

} // namespace qttools
