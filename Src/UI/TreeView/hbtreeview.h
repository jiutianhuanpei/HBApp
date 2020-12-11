#ifndef HBTREEVIEW_H
#define HBTREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include "hbtreemodel.h"

class HBTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit HBTreeView(QWidget *parent = nullptr);

    void setData();

    void appendData(const QList<QVariant> data, const QModelIndex parent);

signals:

public slots:

private:
    HBTreeModel *model;

};

#endif // HBTREEVIEW_H
