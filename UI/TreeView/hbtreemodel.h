#ifndef HBTREEMODEL_H
#define HBTREEMODEL_H

#include <QAbstractItemModel>
#include "hbitemdata.h"
#include <QModelIndex>

class HBTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit HBTreeModel(const QStringList headers, QObject *parent = nullptr);
    ~HBTreeModel();


    void appendData(const QList<QVariant> data, const QModelIndex parent);


private:
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

private:
    HBItemData *rootItem = nullptr;


private:
    HBItemData *getItem(const QModelIndex &index) const;

};

#endif // HBTREEMODEL_H
