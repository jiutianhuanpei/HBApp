#include "hbtreeview.h"
#include <QPalette>
#include <QList>
#include <QDebug>
#include "hbitemdata.h"

HBTreeView::HBTreeView(QWidget *parent) : QTreeView(parent)
{

    setLineWidth(0);
    QStringList headers;
    headers << "First" << "Second";


    model = new HBTreeModel(headers);
    setModel(model);

    connect(this, &HBTreeView::expanded, this, [&](const QModelIndex& index) {

        static_cast<HBItemData *>(index.internalPointer())->description();

    });

    connect(this, &HBTreeView::collapsed, this, [&](const QModelIndex& index) {
        static_cast<HBItemData *>(index.internalPointer())->description();
    });

    QItemSelectionModel *selectmodel = new QItemSelectionModel(model);
    setSelectionModel(selectmodel);
    connect(selectmodel, &QItemSelectionModel::currentChanged, this, [&]() {

        bool hasSelection = !selectionModel()->selection().isEmpty();
        bool hasCurrent = selectionModel()->currentIndex().isValid();


        qDebug() << "has: " << hasSelection << hasCurrent;

        QModelIndex index = selectionModel()->currentIndex();
        qDebug() << index.row() << index.column() << index.data();

    });

}


int a = 0;
int b = 1;

void HBTreeView::setData()
{
    QList<QVariant> list;
    list << a++ << b++;

    qDebug() << __FUNCTION__ << list;


    model->appendData(list, QModelIndex());


}

void HBTreeView::appendData(const QList<QVariant> data, const QModelIndex parent)
{

    if (!parent.isValid())
        return;

    model->appendData(data, parent);

}
