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

#pragma once

#include "core.h"
#include "plugins_loader_instance_filter.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVector>

namespace qtcore {

class QTTOOLS_CORE_EXPORT PluginsLoader
{
public:
    typedef PluginsLoader_InstanceFilter InstanceFilter;

    PluginsLoader();
    ~PluginsLoader();

    bool autoDeletePlugins() const;
    void setAutoDeletePlugins(bool on);

    void addPath(const QString& path);
    void removePath(const QString& path);
    QStringList paths() const;
    void setPaths(const QStringList& paths);

    QStringList fileNameFilters() const;
    void setFileNameFilters(const QStringList& nameFilters);

    void loadPlugins(InstanceFilter* filter, QStringList* errors = NULL);
    void loadPlugins(const QList<InstanceFilter*>& filters, QStringList* errors = NULL);
    void discardPlugin(QObject* plugin);

    QString pluginFileName(const QObject* plugin) const;
    QVector<QObject*> plugins() const;
    template<typename INTERFACE> QVector<INTERFACE*> castPlugins() const;

private:
    class Private;
    Private* const d;
};



// --
// -- Implementation
// --

/*!
 * \brief Returns all loaded plugin root components casted (with qobject_cast<>) to INTERFACE*
 * \tparam INTERFACE Interface type used with qobject_cast<>
 *
 * NULL plugins are not added to the result vector
 */
template<typename INTERFACE>
QVector<INTERFACE *> PluginsLoader::castPlugins() const
{
    QVector<INTERFACE *> typPlugins;
    foreach (QObject* plugin, this->plugins()) {
        INTERFACE* typPlugin = qobject_cast<INTERFACE*>(plugin);
        if (typPlugin != NULL)
            typPlugins.append(typPlugin);
    }
    return typPlugins;
}

} // namespace qtcore
