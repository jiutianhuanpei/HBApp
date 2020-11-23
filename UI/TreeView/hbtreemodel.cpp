#include "hbtreemodel.h"

HBTreeModel::HBTreeModel(const QStringList headers, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString k, headers) {
        rootData << k;
    }

    headerItem = new HBItemData(rootData);
}

QVariant HBTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerItem->data(section);
    }
    return QVariant();
}

QModelIndex HBTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
    HBItemData *parentItem = getItem(parent);
    HBItemData *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    return QModelIndex();
}

QModelIndex HBTreeModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!

    if (!index.isValid())
        return QModelIndex();

    HBItemData *childItem = getItem(index);
    HBItemData *parentItem = childItem->parent();

    if (parentItem == headerItem || parentItem == nullptr)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

int HBTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!

    HBItemData *parentItem = getItem(parent);
    return parentItem->childCount();
}

int HBTreeModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
    return headerItem->columnNum();
}

//bool HBTreeModel::hasChildren(const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//}

//bool HBTreeModel::canFetchMore(const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//    return false;
//}

//void HBTreeModel::fetchMore(const QModelIndex &parent)
//{
//    // FIXME: Implement me!
//}

QVariant HBTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!

    HBItemData *item = getItem(index);
    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}

bool HBTreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!

    HBItemData *parentItem = getItem(parent);

    bool ret = parentItem->insertChildred(row, count, headerItem->columnNum());


    endInsertRows();
    return ret;
}

bool HBTreeModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!

    bool ret = headerItem->insertColumns(column, count);

    endInsertColumns();
    return ret;
}

bool HBTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!

    HBItemData *parentItem = getItem(parent);
    bool ret = parentItem->removeChildren(row, count);


    endRemoveRows();
    return ret;
}

bool HBTreeModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!

    bool ret = headerItem->removeColumns(column, count);

    endRemoveColumns();
    return ret;
}

HBItemData *HBTreeModel::getItem(const QModelIndex &index) const
{

    if (index.isValid())
    {
        HBItemData *item = static_cast<HBItemData *>(index.internalPointer());
        if (item)
            return item;
    }

    return headerItem;
}
