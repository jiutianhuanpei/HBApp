#include "hbitemdata.h"

HBItemData::HBItemData(const QList<QVariant> &data, HBItemData *parent)
{
    m_itemData = data;
    m_parentItem = parent;
}

HBItemData::~HBItemData()
{
    qDeleteAll(m_childItems);
}

void HBItemData::appendChild(HBItemData *child)
{
    //m_childItems.append(child);
	m_childItems.insert(0, child);
}

HBItemData *HBItemData::child(int row)
{
    return m_childItems.value(row);
}

int HBItemData::childCount() const
{
    return m_childItems.count();
}

int HBItemData::columnCount() const
{
    return m_itemData.count();
}

QVariant HBItemData::data(int column) const
{
    return m_itemData.value(column);
}

int HBItemData::row()
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<HBItemData *>(this));

    return 0;
}

HBItemData *HBItemData::parentItem()
{
    return m_parentItem;
}

