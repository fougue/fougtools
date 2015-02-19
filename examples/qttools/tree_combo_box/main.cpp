#include <QApplication>
#include <QtCore/QtDebug>
#include <QtGui/QStandardItemModel>

#include <qttools/gui/tree_combo_box.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QStandardItem* itemRegnum = new QStandardItem("Regnum");
    itemRegnum->appendRow(new QStandardItem("Animalia"));
    itemRegnum->appendRow(new QStandardItem("Plantae"));
    itemRegnum->appendRow(new QStandardItem("Fungi"));
    itemRegnum->appendRow(new QStandardItem("Protista"));
    itemRegnum->appendRow(new QStandardItem("Bacteria"));
    itemRegnum->appendRow(new QStandardItem("Archea"));

    itemRegnum->child(0)->appendRow(new QStandardItem("Eumetazoa"));
    itemRegnum->child(0)->child(0)->appendRow(new QStandardItem("Bilateria"));
    itemRegnum->child(0)->child(0)->appendRow(new QStandardItem("Cnidaria"));
    itemRegnum->child(0)->child(0)->appendRow(new QStandardItem("Ctenophora"));
    itemRegnum->child(0)->child(0)->appendRow(new QStandardItem("Myxozoa"));
    itemRegnum->child(0)->child(0)->appendRow(new QStandardItem("Placozoa"));

    itemRegnum->child(0)->appendRow(new QStandardItem("Porifera"));
    itemRegnum->child(0)->child(1)->appendRow(new QStandardItem("Calcarea"));
    itemRegnum->child(0)->child(1)->appendRow(new QStandardItem("Demospongiae"));
    itemRegnum->child(0)->child(1)->appendRow(new QStandardItem("Hexactinellida"));

    QStandardItemModel* treeModel = new QStandardItemModel;
    treeModel->appendRow(itemRegnum);

    qttools::TreeComboBox treeCombo;
    treeCombo.setModel(treeModel);
    treeCombo.show();
    return app.exec();
}
