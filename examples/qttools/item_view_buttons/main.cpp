#include <functional>

#include <QStandardItemModel>
#include <QApplication>
#include <QHeaderView>
#include <QTreeView>

#include <qttools/gui/item_view_buttons.h>

enum {
    ModelRootItemTag = 1,
    ModelChildItemTag = 2
};

enum {
    ButtonAddChildBtn = 1,
    ButtonRemoveChildBtn = 2
};

enum {
    ItemTypeRole = Qt::UserRole + 1
};

static void handleItemViewButtonClicked(QStandardItemModel* model,
                                        int btnId,
                                        const QModelIndex& index)
{
    static int btnCounter = 0;

    if (btnId == ButtonAddChildBtn) {
        QStandardItem* childItem = new QStandardItem(QString("Child item %1").arg(btnCounter));
        childItem->setData(ModelChildItemTag, ItemTypeRole);
        childItem->setEditable(false);
        model->item(0)->appendRow(childItem);
        ++btnCounter;
    }
    else if (btnId == ButtonRemoveChildBtn) {
        model->removeRow(index.row(), index.parent());
    }
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // Create model with a root item
    QStandardItemModel model;
    QStandardItem* rootItem = new QStandardItem("root-item");
    rootItem->setData(ModelRootItemTag, ItemTypeRole);
    rootItem->setEditable(false);
    model.appendRow(rootItem);

    // Create tree-view
    QTreeView treeView;
    treeView.setExpandsOnDoubleClick(false);
    treeView.setHeaderHidden(true);
    treeView.setModel(&model);
    treeView.expand(rootItem->index());

    // Create buttons
    qttools::ItemViewButtons viewBtns(&treeView);
    viewBtns.installDefaultItemDelegate();

    QIcon iconAdd(":/images/add.png");
    iconAdd.addPixmap(QPixmap(":/images/add_active.png"), QIcon::Active);
    viewBtns.addButton(ButtonAddChildBtn, iconAdd, QString("Add child item"));
    viewBtns.setButtonDetection(ButtonAddChildBtn, ItemTypeRole, ModelRootItemTag);
    viewBtns.setButtonDisplayModes(ButtonAddChildBtn, qttools::ItemViewButtons::DisplayPermanent);

    QIcon iconRem(":/images/remove.png");
    iconRem.addPixmap(QPixmap(":/images/remove_active.png"), QIcon::Active);
    viewBtns.addButton(ButtonRemoveChildBtn, iconRem, QString("Remove child item"));
    viewBtns.setButtonDetection(ButtonRemoveChildBtn, ItemTypeRole, ModelChildItemTag);

    // Connect button "clicked" signal to handler
    QObject::connect(
                &viewBtns,
                &qttools::ItemViewButtons::buttonClicked,
                std::bind(&handleItemViewButtonClicked, &model, std::placeholders::_1, std::placeholders::_2));

    // Run app
    treeView.show();
    return app.exec();
}
