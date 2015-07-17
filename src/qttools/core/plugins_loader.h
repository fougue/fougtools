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
    void loadPlugins(
            const QList<InstanceFilter*>& filters, QStringList* errors = NULL);
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
 * Returns all loaded plugin root components casted (with qobject_cast<>) to
 * INTERFACE*
 *
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
