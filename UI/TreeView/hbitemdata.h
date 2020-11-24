#ifndef HBITEMDATA_H
#define HBITEMDATA_H

#include <QObject>
#include <QVector>
#include <QVariant>

class HBItemData : public QObject
{
    Q_OBJECT
public:
    explicit HBItemData(const QList<QVariant> &data = {}, HBItemData *parent = nullptr);
    ~HBItemData();

    void appendChild(HBItemData *child);

    HBItemData *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row();
    HBItemData *parentItem();


private:
    QList<HBItemData *> m_childItems;
    QList<QVariant> m_itemData;
    HBItemData *m_parentItem;

};

#endif // HBITEMDATA_H
