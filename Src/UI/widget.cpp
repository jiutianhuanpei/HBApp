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

using namespace Base;
using namespace NetTools;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    _InitializeWidgets();
    _InitializeConnects();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::_InitializeWidgets()
{
    qDebug() << "All " << ui->topBar->visiableIndexs();



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



//AddUserWgt *add = new AddUserWgt();

//QRect rect = qApp->activeWindow()->geometry();

//int x = rect.x();
//int y = rect.y();

//x += ((rect.width() - add->width()) / 2.0);
//y += ((rect.height() - add->height()) / 2.0);

//add->move(x, y);
//add->show();
