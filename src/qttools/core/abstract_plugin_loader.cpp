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

#include "qttools/core/abstract_plugin_loader.h"

#include <QtCore/QDir>
#include <QtCore/QHash>
#include <QtCore/QLibrary>
#include <QtCore/QPluginLoader>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>

#include <QtCore/QtDebug>

namespace {

bool isLibrary(const QString& path)
{
  return path.endsWith(".so") || path.endsWith(".dll");
}

} // Anonymous namespace

namespace qttools {

/*! \class AbstractPluginLoaderPrivate
 *  \brief Internal (pimpl of AbstractPluginLoader)
 */
class AbstractPluginLoaderPrivate
{
public:
  AbstractPluginLoaderPrivate() :
    autoDeletePlugins(true)
  {
    this->plugins.reserve(100);
    this->pluginLoaders.reserve(100);
  }

  QVector<QObject*> plugins;
  QVector<QPluginLoader*> pluginLoaders;
  QHash<const QObject*, QString> pluginFilenames;
  bool autoDeletePlugins;
  QString loadingFolder;
};


/*! \class AbstractPluginLoader
 *  \brief Base abstract class for dynamic loading of plugins
 *
 *  AbstractPluginLoader loads plugin DLLs from a specified folder
 *  (see loadPlugins()).
 *
 *  AbstractPluginLoader cannot be used as is, it must be redefined to call
 *  loadPlugins() with the right folder. In most cases loadPlugins() should
 *  be called from within the constructor of the descendant class.
 */

AbstractPluginLoader::AbstractPluginLoader() :
  d_ptr(new AbstractPluginLoaderPrivate)
{
}

AbstractPluginLoader::~AbstractPluginLoader()
{
  Q_D(AbstractPluginLoader);
  foreach (QPluginLoader* pluginLoader, d->pluginLoaders) {
    if (pluginLoader != 0) {
      if (this->autoDeletePlugins())
        pluginLoader->unload();
      delete pluginLoader;
    }
  }
  delete d;
}

bool AbstractPluginLoader::autoDeletePlugins() const
{
  Q_D(const AbstractPluginLoader);
  return d->autoDeletePlugins;
}

QString AbstractPluginLoader::loadingFolder() const
{
  Q_D(const AbstractPluginLoader);
  return d->loadingFolder;
}

QString AbstractPluginLoader::filename(const QObject* plugin) const
{
  Q_D(const AbstractPluginLoader);
  if (d->pluginFilenames.contains(plugin))
    return d->pluginFilenames.value(plugin);
  return QString();
}

QVector<QObject*> AbstractPluginLoader::plugins()
{
  Q_D(AbstractPluginLoader);
  return d->plugins;
}

const QVector<QObject*>& AbstractPluginLoader::plugins() const
{
  Q_D(const AbstractPluginLoader);
  return d->plugins;
}

void AbstractPluginLoader::setAutoDeletePlugins(bool v)
{
  Q_D(AbstractPluginLoader);
  d->autoDeletePlugins = v;
}

void AbstractPluginLoader::setLoadingFolder(const QString& folder)
{
  Q_D(AbstractPluginLoader);
  d->loadingFolder = folder;
}

void AbstractPluginLoader::loadPlugins(const QRegExp& fileRx,
                                       QVector<QString>* errors)
{
  Q_D(AbstractPluginLoader);
  const QDir pluginsFolder(this->loadingFolder());
  QStringList entries(pluginsFolder.entryList(QDir::Files));
  foreach (const QString& entry, entries) {
    if (fileRx.indexIn(entry) != -1 && ::isLibrary(entry)) {
      // Try to load the plugin
#ifdef DEBUG_ABSTRACT_PLUGIN_LOADER
      qDebug() << "try to load" << entry;
#endif // DEBUG_ABSTRACT_PLUGIN_LOADER
      QPluginLoader* pluginLoader = new QPluginLoader(pluginsFolder.absoluteFilePath(entry));
      QObject* plugin = pluginLoader->instance();
      // Is the plugin compatible ?
      if (this->isPluginCompatible(plugin)) {
        d->plugins.append(plugin);
        d->pluginLoaders.append(pluginLoader);
        d->pluginFilenames.insert(plugin, entry);
      }
      else {
#ifdef DEBUG_ABSTRACT_PLUGIN_LOADER
        qDebug() << "  not added";
#endif // DEBUG_ABSTRACT_PLUGIN_LOADER
        if (errors != 0)
          //: %1 holds the path to a plugin (DLL)
          //: %2 holds an error description
          errors->append(QObject::tr("Failed to load plugin "
                                     "(maybe wrong interface) %1 : %2")
                         .arg(pluginLoader->fileName())
                         .arg(pluginLoader->errorString()));
        pluginLoader->unload();
        delete pluginLoader;
      } // end if (this->isPluginCompatible(plugin))
    } // end if (fileRx.indexIn(entry) != -1)
  } // end foreach ()
}

void AbstractPluginLoader::discardPlugin(QObject* plugin)
{
  Q_D(AbstractPluginLoader);
  for (int i = 0; i < d->plugins.size(); ++i) {
    if (plugin == d->plugins.at(i)) {
      d->plugins.remove(i);
      if (this->autoDeletePlugins())
        d->pluginLoaders.at(i)->unload();
      delete d->pluginLoaders.at(i);
      d->pluginLoaders.remove(i);
    }
  }
  d->pluginFilenames.remove(plugin);
}

} // namespace qttools
