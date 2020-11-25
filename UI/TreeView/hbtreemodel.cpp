#include "hbtreemodel.h"
#include <QDebug>

HBTreeModel::HBTreeModel(const QStringList headers, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    foreach (QString k, headers) {
        rootData << k;
    }

    rootItem = new HBItemData(rootData);
	configData();
}

HBTreeModel::~HBTreeModel()
{
    delete rootItem;
}

void HBTreeModel::appendData(const QList<QVariant> data, const QModelIndex index)
{
    if (data.count() == 0)
        return;

    HBItemData *parentItem = getItem(index);

    beginInsertRows(index, parentItem->childCount(), parentItem->childCount() + 1);

    HBItemData *addItem = new HBItemData(data);
    parentItem->appendChild(addItem);

    endInsertRows();





}

QVariant HBTreeModel::data(const QModelIndex &index, int role) const
{
    //qDebug() << __FUNCTION__;
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    HBItemData *item = static_cast<HBItemData *>(index.internalPointer());
    return item->data(index.column());
}

QVariant HBTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //qDebug() << __FUNCTION__;
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);
    return QVariant();
}

QModelIndex HBTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    //qDebug() << __FUNCTION__;

    if (!hasIndex(row, column, parent))
        return QModelIndex();

    HBItemData *parentItem = getItem(parent);

    HBItemData *childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else {
        return QModelIndex();
    }
}

QModelIndex HBTreeModel::parent(const QModelIndex &child) const
{
    //qDebug() << __FUNCTION__;

    if (!child.isValid())
        return QModelIndex();

    HBItemData *childItem = getItem(child);
    HBItemData *parentItem = childItem->parentItem();

    if (parentItem == rootItem || parentItem == nullptr)
        return QModelIndex();
    return createIndex(parentItem->row(), 0, parentItem);
}

int HBTreeModel::rowCount(const QModelIndex &parent) const
{
    //qDebug() << __FUNCTION__;

    if (parent.column() > 0)
        return 0;

    HBItemData *parentItem = getItem(parent);
    return parentItem->childCount();
}

int HBTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<HBItemData *>(parent.internalPointer())->columnCount();

    return rootItem->columnCount();
}


HBItemData *HBTreeModel::getItem(const QModelIndex &index) const
{

    if (index.isValid())
    {
        HBItemData *item = static_cast<HBItemData *>(index.internalPointer());
        if (item)
            return item;
    }

    return rootItem;
}

void HBTreeModel::configData()
{

	HBItemData *first = new HBItemData(QList<QVariant>() << "A" << "AA", rootItem);

	HBItemData *f1 = new HBItemData(QList<QVariant>() << "a" << "aa", first);
	first->appendChild(f1);
	HBItemData *f2 = new HBItemData(QList<QVariant>() << "aa" << "aaa", first);
	first->appendChild(f2);

	HBItemData *second = new HBItemData(QList<QVariant>() << "B" << "BB", rootItem);
	HBItemData *s1 = new HBItemData(QList<QVariant>() << "b" << "bb", second);
	second->appendChild(s1);
	HBItemData *s2 = new HBItemData(QList<QVariant>() << "bb" << "bbb", second);
	second->appendChild(s2);


	HBItemData *four = new HBItemData(QList<QVariant>() << "D" << "DD", rootItem);


	HBItemData *third = new HBItemData(QList<QVariant>() << "C" << "CC", rootItem);
	HBItemData *t1 = new HBItemData(QList<QVariant>() << "cc" << "ccc", third);
	third->appendChild(t1);
	HBItemData *t2 = new HBItemData(QList<QVariant>() << "ccc" << "cc", third);
	third->appendChild(t2);
	HBItemData *t3 = new HBItemData(QList<QVariant>() << "cccc" << "ccccc", third);
	third->appendChild(t3);



	rootItem->appendChild(four);
	rootItem->appendChild(third);
	rootItem->appendChild(second);
	rootItem->appendChild(first);
}
