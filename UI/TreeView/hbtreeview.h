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

signals:

public slots:

private:
    HBTreeModel *model;

};

#endif // HBTREEVIEW_H
