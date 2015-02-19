#include "test_qttools_gui.h"

#include "../src/qttools/gui/qstandard_item_explorer.h"

#include <QtCore/QtDebug>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

void TestQtToolsGui::QStandardItemExplorer_test()
{
    QStandardItemModel itemModel;

    auto rootItem = new QStandardItem(QLatin1String("root"));
    itemModel.appendRow(rootItem);

    auto item1 = new QStandardItem(QLatin1String("item_1"));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_1")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_2")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_3")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_4")));

    auto item2 = new QStandardItem(QLatin1String("item_2"));

    rootItem->appendRow(item1);
    rootItem->appendRow(item2);

    qttools::QStandardItemExplorer explorer(&itemModel);
    QCOMPARE(explorer.current(), itemModel.invisibleRootItem());
    explorer.goNext();
    QCOMPARE(explorer.current(), rootItem);
    explorer.goNext();
    QCOMPARE(explorer.current(), item1);
    explorer.goNext();
    QCOMPARE(explorer.current(), item2);
    explorer.goNext();
    for (int i = 0; i < item1->rowCount(); ++i) {
        QCOMPARE(explorer.current(), item1->child(i));
        explorer.goNext();
    }
    QCOMPARE(explorer.atEnd(), true);
}
