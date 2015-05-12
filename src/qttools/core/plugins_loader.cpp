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

#include "plugins_loader.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QHash>
#include <QtCore/QLibrary>
#include <QtCore/QPluginLoader>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>

#include <QtCore/QtDebug>

namespace qtcore {

/*! \brief Internal (pimpl of PluginsLoader)
 */
class PluginsLoader::Private
{
public:
    Private();

    void releasePlugins();

    static bool filterAccepts(
            const QList<InstanceFilter*>& filters,
            QPluginLoader* pluginLoader,
            QString* filterError);
    static bool isLibrary(const QString &path);

    QVector<QObject*> m_plugins;
    QVector<QPluginLoader*> m_pluginLoaders;
    QHash<const QObject*, QString> m_pluginFileNames;
    bool m_autoDeletePlugins;
    QStringList m_pluginPaths;
    QStringList m_fileNameFilters;
};

PluginsLoader::Private::Private()
    : m_autoDeletePlugins(true)
{
    m_plugins.reserve(100);
    m_pluginLoaders.reserve(100);
}

void PluginsLoader::Private::releasePlugins()
{
    foreach (QPluginLoader* pluginLoader, m_pluginLoaders) {
        if (pluginLoader != NULL) {
            if (m_autoDeletePlugins)
                pluginLoader->unload();
            delete pluginLoader;
        }
    }

    m_pluginLoaders.clear();
    m_plugins.clear();
    m_pluginFileNames.clear();
}

bool PluginsLoader::Private::filterAccepts(
        const QList<InstanceFilter *> &filters,
        QPluginLoader* pluginLoader,
        QString* filterError)
{
    foreach (InstanceFilter* filter, filters) {
        if (!filter->accepts(pluginLoader, filterError))
            return false;
    }
    return true;
}

bool PluginsLoader::Private::isLibrary(const QString &path)
{
    QStringList suffixList;
#if defined(Q_OS_WIN) || defined(Q_OS_WIN32)
    suffixList << QLatin1String(".dll");
#elif defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
    suffixList << QLatin1String(".so");
#elif defined(Q_OS_MAC)
    suffixList << QLatin1String(".dylib")
               << QLatin1String(".bundle")
               << QLatin1String(".so");
#endif

    foreach (const QString& suffix, suffixList)
        return path.endsWith(suffix);
    return false;
}

/*!
 * \class PluginsLoader
 * \brief Provides run-time loading of Qt-based plugins located into search paths
 *
 * \headerfile plugins_loader.h <qttools/core/plugins_loader.h>
 * \ingroup qttools_core
 *
 */

PluginsLoader::PluginsLoader()
    : d(new Private)
{
}

PluginsLoader::~PluginsLoader()
{
    d->releasePlugins();
    delete d;
}

/*!
 * \brief Is auto-deletion of plugins enabled ?
 *
 * If plugins auto-deletion is enabled, PluginsLoader will automatically delete
 * plugins on destruction of this object.
 *
 * \note autoDeletePlugins() is enabled by default.
 *
 * \sa setAutoDeletePlugins()
 */
bool PluginsLoader::autoDeletePlugins() const
{
    return d->m_autoDeletePlugins;
}

/*!
 * Enables plugins auto-deletion if \p on is true; otherwise auto-deletion is
 * disabled
 *
 * \sa autoDeletePlugins()
 */
void PluginsLoader::setAutoDeletePlugins(bool on)
{
    d->m_autoDeletePlugins = on;
}

/*!
 * \brief Appends path to the plugins path list
 *
 * If \p path is empty or already in the path list, the path list is not changed.
 */
void PluginsLoader::addPath(const QString &path)
{
    if (!path.trimmed().isEmpty() || !d->m_pluginPaths.contains(path))
        d->m_pluginPaths.append(path);
}

/*!
 * \brief Removes \p path from the list of plugin paths
 */
void PluginsLoader::removePath(const QString &path)
{
    d->m_pluginPaths.removeOne(path);
}

/*!
 * \brief Returns the paths used when loading plugins at run-time (with loadPlugins())
 * \sa addPath() setPaths()
 */
QStringList PluginsLoader::paths() const
{
    return d->m_pluginPaths;
}

/*!
 * \brief Sets the list of directories to search when loading plugins to \p paths
 *
 * All existing paths will be deleted and the path list will consist of the
 * paths given in \p paths.
 * \sa addPath(), removePath(), paths()
 */
void PluginsLoader::setPaths(const QStringList &paths)
{
    d->m_pluginPaths = paths;
}

/*!
 * \brief Returns the list set with setFileNameFilters()
 */
QStringList PluginsLoader::fileNameFilters() const
{
    return d->m_fileNameFilters;
}

/*! \brief Sets the name filters used by loadPlugins()
 *
 *  Each name filter is a wildcard (globbing) filter that understands * and ?
 *  wildcards.
 *
 *  \sa QDir::setNameFilters()
 */
void PluginsLoader::setFileNameFilters(const QStringList &nameFilters)
{
    d->m_fileNameFilters = nameFilters;
}

/*!
 * Returns file name of a loaded plugin object (e.g. libmy_plugin.so,
 * other_plugin.dll, ...)
 *
 *  \p plugin must have been successfully loaded with loadPlugins()
 */
QString PluginsLoader::pluginFileName(const QObject* plugin) const
{
    auto it = d->m_pluginFileNames.find(plugin);
    if (it != d->m_pluginFileNames.constEnd())
        return it.value();
    return QString();
}

/*!
 * \brief Returns all loaded plugin root components
 */
QVector<QObject*> PluginsLoader::plugins() const
{
    return d->m_plugins;
}

void PluginsLoader::loadPlugins(InstanceFilter *filter, QStringList *errors)
{
    QList<InstanceFilter*> filters;
    filters.append(filter);
    this->loadPlugins(filters, errors);
}

/*!
 * \brief Loads plugins, any error is reported in \p errors
 */
void PluginsLoader::loadPlugins(
        const QList<InstanceFilter *> &filters, QStringList *errors)
{
    d->releasePlugins();

    foreach (const QString& path, d->m_pluginPaths) {
        QDir pluginDir(path);
        const QStringList entryList(
                    pluginDir.entryList(d->m_fileNameFilters, QDir::Files));
        foreach (const QString& entry, entryList) {
            if (!Private::isLibrary(entry))
                continue;

            // Test plugin loader against filters
            auto pluginLoader =
                    new QPluginLoader(pluginDir.absoluteFilePath(entry));
            QString filterError;
            const bool pluginAccepted =
                    Private::filterAccepts(filters, pluginLoader, &filterError);

            if (pluginAccepted) {
                QObject* pluginInstance = pluginLoader->instance();
                d->m_plugins.append(pluginInstance);
                d->m_pluginLoaders.append(pluginLoader);
                d->m_pluginFileNames.insert(pluginInstance, entry);
            }
            else {
                if (errors != NULL) {
                    //: %1 holds the path to a plugin (DLL)
                    //: %2 holds an error description
                    errors->append(
                                QCoreApplication::translate(
                                    "qtcore::PluginsLoader",
                                    "Failed to load plugin %1, error : %2")
                                .arg(pluginLoader->fileName())
                                .arg(!filterError.isEmpty() ?
                                         filterError :
                                         pluginLoader->errorString()));
                }
                pluginLoader->unload();
                delete pluginLoader;
            }
        } // end foreach ()
    } // end foreach ()
}

/*! \brief Removes a previously loaded plugin object
 */
void PluginsLoader::discardPlugin(QObject* plugin)
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
    d->m_pluginFileNames.remove(plugin);
}

} // namespace qtcore
