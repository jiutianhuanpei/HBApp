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
#include "../MessageCenter/messagecore.h"
#include <QCursor>
#include <QRect>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

using namespace Base;
using namespace NetTools;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground, true);

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

    foreach (QWidget *w, findChildren<QWidget*>()) {
        w->setMouseTracking(true);
        qDebug() << "AAAA" << w;
    }

    setMouseTracking(true);


    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(0, 0);
    effect->setColor(QColor(0,0,0,90));
    effect->setBlurRadius(15);
    ui->bgWgt->setGraphicsEffect(effect);

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
                ui->shadowLayout->setContentsMargins(9, 9, 9, 9);
                showNormal();
            }
            else
            {
                ui->shadowLayout->setContentsMargins(0, 0, 0, 0);
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

    QPoint topLeft = this->mapToGlobal(rect.topLeft()); //左上
    topLeft.setX(topLeft.x() + shadowSpace);
    topLeft.setY(topLeft.y() + shadowSpace);

    QPoint rightBottom = this->mapToGlobal(rect.bottomRight());
    rightBottom.setX(rightBottom.x() - shadowSpace);
    rightBottom.setY(rightBottom.y() - shadowSpace);

    int x = point.x(); //Mouse point
    int y = point.y();

    int padding = 15;

    if (x < topLeft.x() || x > rightBottom.x() || y < topLeft.y() || y > rightBottom.y())
    {
        m_Direction = Outside;

    }
    else if ((x <= topLeft.x() + padding) && (y >= topLeft.y() + padding) && (y <= rightBottom.y() - padding))
    {
        m_Direction = Left;
    }
    else if ((x <= topLeft.x() + padding) && (y < topLeft.y() + padding))
    {
        m_Direction = LeftTop;
    }
    else if ((x <= topLeft.x() + padding) && (y >= rightBottom.y() - padding))
    {
        m_Direction = LeftBottom;
    }
    else if ((x <= rightBottom.x() - padding) && (y <= topLeft.y() + padding))
    {
        m_Direction = Top;
    }
    else if ((x <= rightBottom.x() - padding) && (y < topLeft.y() + ui->topBar->height()))
    {
        m_Direction = Moveside;
    }
    else if ((x <= rightBottom.x() - padding) && (y < rightBottom.y() - padding))
    {
        m_Direction = Inside;
    }
    else if ((x <= rightBottom.x() - padding) && (y >= rightBottom.y() - padding))
    {
        m_Direction = Bottom;
    }
    else if ((x > rightBottom.x() - padding) && (y < topLeft.y() + padding))
    {
        m_Direction = RightTop;
    }
    else if ((x > rightBottom.x() - padding) && (y < rightBottom.y() - padding))
    {
        m_Direction = Right;
    }
    else
    {
        m_Direction = RightBottom;
    }

        qDebug() << "Current region: " << m_Direction;

    if (m_Direction == Left || m_Direction == Right)
    {
        setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (m_Direction == Top || m_Direction == Bottom)
    {
        setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if (m_Direction == Inside || m_Direction == Outside || m_Direction == Moveside)
    {
        setCursor(QCursor(Qt::ArrowCursor));
    }
    else if (m_Direction == LeftTop || m_Direction == RightBottom)
    {
        setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (m_Direction == LeftBottom || m_Direction == RightTop)
    {
        setCursor(QCursor(Qt::SizeBDiagCursor));
    }


}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint globalPoint = event->globalPos();   //榧犳爣鍏ㄥ眬鍧愭爣

    QRect rect = this->rect();
    QPoint topLeft = mapToGlobal(rect.topLeft());

    QPoint bottomRight = mapToGlobal(rect.bottomRight());



    if (!(event->buttons() & Qt::LeftButton))
    {
        region(globalPoint);
    }
    else
    {
//        topLeft.setX(topLeft.x() - shadowSpace);
//        topLeft.setY(topLeft.y() - shadowSpace);
//        bottomRight.setX(bottomRight.x() + shadowSpace);
//        bottomRight.setY(bottomRight.y() + shadowSpace);


        if (m_Direction == Moveside)
        {
            QPoint ptemp=event->globalPos();
            ptemp=ptemp-lastPoint;  //鼠标移动的偏移量
            ptemp=ptemp+pos();
            move(ptemp);
        }
        else
        {
            QRect newRect = QRect(topLeft, bottomRight);

            int mouseY = globalPoint.y();
            int mouseX = globalPoint.x();

            switch (m_Direction) {
            case LeftTop:
            {
                if (bottomRight.x() - mouseX <= minimumWidth())
                    newRect.setX(topLeft.x());
                else
                    newRect.setX(mouseX - shadowSpace);

                if (bottomRight.y() - mouseY <= minimumHeight())
                    newRect.setY(topLeft.y());
                else
                    newRect.setY(mouseY - shadowSpace);

                break;
            }
            case Top:
            {
                if (bottomRight.y() - mouseY <= minimumHeight())
                    newRect.setY(topLeft.y());
                else
                    newRect.setY(mouseY - shadowSpace);

                break;
            }
            case RightTop:
            {
                if (mouseX - topLeft.x() <= minimumWidth())
                    newRect.setRight(bottomRight.x());
                else
                    newRect.setRight(mouseX + shadowSpace);

                if (bottomRight.y() - mouseY <= minimumHeight())
                    newRect.setY(topLeft.y());
                else
                    newRect.setY(mouseY - shadowSpace);
                break;
            }
            case Right:
            {
                if (mouseX - topLeft.x() <= minimumWidth())
                    newRect.setRight(bottomRight.x());
                else
                    newRect.setRight(mouseX + shadowSpace);

                break;
            }
            case RightBottom:
            {
                if (mouseX - topLeft.x() <= minimumWidth())
                    newRect.setRight(bottomRight.x());
                else
                    newRect.setRight(mouseX + shadowSpace);

                if (mouseY - topLeft.y() <= minimumHeight())
                    newRect.setHeight(bottomRight.y() - topLeft.y());
                else
                    newRect.setHeight(mouseY + shadowSpace - topLeft.y());
                break;
                break;
            }
            case Bottom:
            {
                if (mouseY - topLeft.y() <= minimumHeight())
                    newRect.setHeight(bottomRight.y() - topLeft.y());
                else
                    newRect.setHeight(mouseY + shadowSpace - topLeft.y());
                break;
            }
            case LeftBottom:
            {
                if (bottomRight.x() - mouseX < minimumWidth())
                    newRect.setX(topLeft.x());
                else
                    newRect.setX(mouseX - shadowSpace);

                if (mouseY - topLeft.y() <= minimumHeight())
                    newRect.setHeight(bottomRight.y() - topLeft.y());
                else
                    newRect.setHeight(mouseY + shadowSpace - topLeft.y());
                break;
            }
            case Left:
            {
                if (bottomRight.x() - mouseX < minimumWidth())
                    newRect.setX(topLeft.x());
                else
                    newRect.setX(mouseX - shadowSpace);
                break;
            }
            default:
                break;
            }
            setGeometry(newRect);
        }
    }


    lastPoint = event->globalPos();
    event->ignore();
}

