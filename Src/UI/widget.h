#ifndef WIDGET_H
#define WIDGET_H

#include <QMouseEvent>
#include <QWidget>
#include "hbwebview.h"
#include "uiheader.h"

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

};

#endif // WIDGET_H
