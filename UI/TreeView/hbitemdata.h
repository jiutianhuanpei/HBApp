#ifndef HBITEMDATA_H
#define HBITEMDATA_H

#include <QObject>
#include <QVector>
#include <QVariant>

class HBItemData : public QObject
{
    Q_OBJECT
public:
    explicit HBItemData(const QVector<QVariant> data = {}, HBItemData *parent = nullptr);



    HBItemData *child(int index);
    HBItemData *parent();
    int childCount();
    int columnNum();
    QVariant data(int column);

    int childNumber();

    bool insertChildred(int position, int count, int columns);
    bool insertColumns(int position, int column);

    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);


private:
    QVector<QVariant> itemData;
    QVector<HBItemData *> childItems;
    HBItemData *parentItem;

};

#endif // HBITEMDATA_H
