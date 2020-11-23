#include "hbitemdata.h"

HBItemData::HBItemData(const QVector<QVariant> data, HBItemData *parent)
{
    itemData = data;
    parentItem = parent;
}

HBItemData *HBItemData::child(int index)
{
    return childItems.value(index);
}

HBItemData *HBItemData::parent()
{
    return parentItem;
}

int HBItemData::childCount()
{
    return childItems.count();
}

int HBItemData::columnNum()
{
    return itemData.count();
}

QVariant HBItemData::data(int column)
{
    return itemData.value(column);
}

int HBItemData::childNumber()
{
    if (parentItem)
    {
        return parentItem->childItems.indexOf(const_cast<HBItemData *>(this));
    }
    return 0;
}

bool HBItemData::insertChildred(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        HBItemData *item = new HBItemData(data, this);
        childItems.insert(position, item);
    }
    return true;
}

bool HBItemData::insertColumns(int position, int column)
{

    if (position < 0 || position > itemData.size())
        return false;

    for (int c = 0; c < column; ++c) {
        itemData.insert(position, QVariant());
    }

    foreach (HBItemData *child, childItems) {
        child->insertColumns(position, column);
    }
    return true;
}

bool HBItemData::removeChildren(int position, int count)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int row = 0; row < count; ++row) {
        delete childItems.takeAt(position);
    }
    return true;

}

bool HBItemData::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column) {
        itemData.remove(position);
    }

    foreach (HBItemData *child, childItems) {
        child->removeColumns(position, columns);
    }
    return true;
}
