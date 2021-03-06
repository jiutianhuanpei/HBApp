#ifndef WIDGET_H
#define WIDGET_H

#include <QMouseEvent>
#include <QWidget>
#include "hbwebview.h"
#include "uiheader.h"
#include "TreeView/hbtreeview.h"
#include <QStackedWidget>
#include "wgtintelligentmonitor.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void _InitializeWidgets();
    void _InitializeConnects();
    void didClickedMenu(MenuIndex index);

    void region(const QPoint& point);


protected:
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    HBTreeView  *m_treeView;
    QStackedWidget *m_rightWgt;

    WgtIntelligentMonitor *m_intelligent;

    MousePoint m_Direction;
    QPoint lastPoint;
    int shadowSpace = 9;

};

#endif // WIDGET_H
