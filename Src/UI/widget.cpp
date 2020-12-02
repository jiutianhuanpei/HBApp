#include "widget.h"
#include "ui_widget.h"
#include "../DB/hbdatabase.h"
#include <QDebug>
#include "adduserwgt.h"
#include <QGuiApplication>
#include "TreeView/hbitemdata.h"
#include "../Base/base.h"

#include "../Net/netmanager.h"
#include <QStackedWidget>
#include "../Src/MessageCenter/messagecore.h"

using namespace Base;
using namespace NetTools;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | windowFlags());

    _InitializeWidgets();
    _InitializeConnects();

    ui->stackedWidget->setCurrentIndex(BigScreen);
    ui->topBar->setCurrentIndex(BigScreen);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::_InitializeWidgets()
{
    foreach (MenuIndex index, ui->topBar->visiableIndexs()) {

        switch (index) {
        case BigScreen:
        {
            QWidget *main = new QWidget;
            ui->stackedWidget->insertWidget(BigScreen, main);
            break;
        }
        case Monitor:
        {
            QWidget *main = new QWidget;
            ui->stackedWidget->insertWidget(Monitor, main);
            break;
        }
        case PersonMgr:
        {
            HBWebView *webView = new HBWebView;
            ui->stackedWidget->insertWidget(PersonMgr, webView);
            break;
        }
        case Poll:
        {
            QWidget *main = new QWidget;
            ui->stackedWidget->insertWidget(Poll, main);
            break;
        }
        case Map:
        {
            HBWebView *webView = new HBWebView;
            ui->stackedWidget->insertWidget(Web, webView);
            break;
        }
        case Web:
        {
            HBWebView *webView = new HBWebView;
            ui->stackedWidget->insertWidget(Web, webView);
            break;
        }

        default:
            break;
        }
    }

}

void Widget::_InitializeConnects()
{
    connect(ui->topBar, &TopBarWgt::signal_didClickedMenu, this, &Widget::didClickedMenu);
    connect(MsgInset(), &MessageCore::signal_windowZoom, this, [&](WindowZoom zoom) {
        if (zoom == Close)
        {
            close();
        }
        else if (zoom == Min)
        {
            qDebug() << "need min";
            //           showMinimized();
            setWindowState(Qt::WindowMinimized);
        }
        else
        {
            if (isFullScreen())
            {
                showNormal();
            }
            else
            {
                showFullScreen();
            }
        }

    });

}

void Widget::didClickedMenu(MenuIndex index)
{
    ui->stackedWidget->setCurrentIndex(index);

    qDebug() << "DID clicked: " << index << ui->stackedWidget->currentWidget();

    switch (index) {
    case BigScreen:
    {

        break;
    }
    case Monitor:
    {

        break;
    }
    case PersonMgr:
    {
        ((HBWebView *)ui->stackedWidget->currentWidget())->load(QUrl("http://www.baidu.com"));
        break;
    }
    case Poll:
    {

        break;
    }
    case Map:
    {
        ((HBWebView *)ui->stackedWidget->currentWidget())->load(QUrl("http://www.qq.com"));
        break;
    }
    case Web:
    {
        ((HBWebView *)ui->stackedWidget->currentWidget())->load(QUrl("http://www.shenhongbang.cc"));
        break;
    }

    default:
        break;
    }
}

void Widget::region(const QPoint &point)
{
    QRect rect = this->rect();

    QPoint topLeft = this->mapToGlobal(rect.topLeft()); //将左上角的(0,0)转化为全局坐标
    QPoint rightBottom = this->mapToGlobal(rect.bottomRight());

    int x = point.x(); //当前鼠标的坐标
    int y = point.y();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint globalPoint = event->globalPos();   //鼠标全局坐标

    QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
    QPoint topLeft = mapToGlobal(rect.topLeft());
    QPoint bottomRight = mapToGlobal(rect.bottomRight());
}



//AddUserWgt *add = new AddUserWgt();

//QRect rect = qApp->activeWindow()->geometry();

//int x = rect.x();
//int y = rect.y();

//x += ((rect.width() - add->width()) / 2.0);
//y += ((rect.height() - add->height()) / 2.0);

//add->move(x, y);
//add->show();
