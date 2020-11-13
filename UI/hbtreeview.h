#ifndef HBTREEVIEW_H
#define HBTREEVIEW_H

#include <QWidget>
#include <QTreeView>

class HBTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit HBTreeView(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // HBTREEVIEW_H
