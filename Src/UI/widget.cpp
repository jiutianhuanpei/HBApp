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
#include "../Net/WebImage/hbwebimage.h"

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

    ui->topBar->setCurrentIndex(BigScreen);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::_InitializeWidgets()
{


    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(0, 0);
    effect->setColor(QColor(0,0,0,90));
    effect->setBlurRadius(15);
    ui->bgWgt->setGraphicsEffect(effect);

    m_treeView = new HBTreeView;
    m_treeView->setData();
    m_treeView->setMaximumWidth(200);
    m_treeView->setMinimumWidth(50);
    m_rightWgt = new QStackedWidget;

    ui->splitter->addWidget(m_treeView);
    ui->splitter->addWidget(m_rightWgt);
    ui->splitter->setSizes(QList<int>() << 3 << 7);




//    QLabel *imgView = new QLabel;
//    m_rightWgt->addWidget(imgView);

    m_intelligent = new WgtIntelligentMonitor;
    m_rightWgt->addWidget(m_intelligent);

    foreach (QWidget *w, findChildren<QWidget*>()) {
        w->setMouseTracking(true);
//        qDebug() << "AAAA" << w;
    }

    setMouseTracking(true);
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
    QLabel *lbl = (QLabel *)m_rightWgt->widget(0);

    switch (index) {
    case BigScreen:
    {

        break;
    }
    case Monitor:
    {
//        manager.fetchImage("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1607335577675&di=8725ab93d31f6b07b7964bb6b20529fd&imgtype=0&src=http%3A%2F%2Fa4.att.hudong.com%2F27%2F67%2F01300000921826141299672233506.jpg");


        HBWebImage::setImage("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1607342747797&di=48acf8187763ecbde20ac731af557a0a&imgtype=0&src=http%3A%2F%2Fa0.att.hudong.com%2F30%2F29%2F01300000201438121627296084016.jpg", lbl);
        break;
    }
    case PersonMgr:
    {
        HBWebImage::setImage("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1607342747797&di=b2133791c6c57624aea53fbe3af63f95&imgtype=0&src=http%3A%2F%2Fa1.att.hudong.com%2F24%2F78%2F20300000291746133783784887147.jpg", lbl);
        break;
    }
    case Poll:
    {
        HBWebImage::setImage("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1607342747797&di=ba0d45e41029a47846b5e304f4b64fe8&imgtype=0&src=http%3A%2F%2Fa3.att.hudong.com%2F35%2F34%2F19300001295750130986345801104.jpg", lbl);
        break;
    }
    case Map:
    {
        HBWebImage::setImage("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1607342747793&di=01be71ee7845765323dac9d8d46b2014&imgtype=0&src=http%3A%2F%2Fa3.att.hudong.com%2F61%2F98%2F01300000248068123885985729957.jpg", lbl);
        break;
    }
    case Web:
    {

        break;
    }

    default:
        break;
    }
}

void Widget::region(const QPoint &point)
{
    QRect rect = this->rect();

    QPoint leftTop = this->mapToGlobal(rect.topLeft()); //左上
    leftTop.setX(leftTop.x() + shadowSpace);
    leftTop.setY(leftTop.y() + shadowSpace);

    QPoint rightBottom = this->mapToGlobal(rect.bottomRight());
    rightBottom.setX(rightBottom.x() - shadowSpace);
    rightBottom.setY(rightBottom.y() - shadowSpace);

    int x = point.x(); //Mouse point
    int y = point.y();

    int padding = 15;


    MousePoint xPoint = Out;
    MousePoint yPoint = Out;


    if (x >= leftTop.x() && (x <= leftTop.x() + padding))
        xPoint = Low;
    else if (x < rightBottom.x() - padding)
        xPoint = Mid;
    else if ((x >= rightBottom.x() - padding) && x <= rightBottom.x())
        xPoint = Hight;

    if (y >= leftTop.y() && (y <= leftTop.y() + padding))
        yPoint = Low;
    else if (y < rightBottom.y() - padding)
        yPoint = Mid;
    else if ((y >= rightBottom.y() - padding) && y <= rightBottom.y())
        yPoint = Hight;

    do {
		
        if (xPoint == Out || yPoint == Out)
        {
            m_Direction = Out;
            break;
        }

        m_Direction = (MousePoint)(xPoint << yPoint);

        if (m_Direction == CenterSide)
        {
            if (y <= leftTop.y() + ui->topBar->height())
                m_Direction = MoveSide;
            break;
        }
    } while (0);

//    qDebug() << "Current region: " << m_Direction;

    if (m_Direction == Left || m_Direction == Right)
    {
        setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (m_Direction == Top || m_Direction == Bottom)
    {
        setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if (m_Direction == CenterSide || m_Direction == MoveSide || m_Direction == Out)
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
        if (m_Direction == MoveSide)
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

