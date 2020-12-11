#include "hbwebimage.h"
#include <QDebug>

HBWebImage::HBWebImage(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QPixmap>("QPixmap");
    qRegisterMetaType<QString>("QString");

//    m_thread = new QThread;

    m_manager = new HBWebImageManager();

    m_manager->moveToThread(&m_thread);

    connect(this, &HBWebImage::signalSetImage, m_manager, &HBWebImageManager::fetchImage);

    connect(&m_thread, &QThread::finished, this, &HBWebImage::deleteLater);

    m_thread.start();
}

HBWebImage::~HBWebImage()
{
//    delete m_thread;
    delete m_manager;
    qDebug() << __FUNCTION__;
}

void HBWebImage::setImage(const QString urlStr, QLabel *imgView)
{

    HBWebImage *image = new HBWebImage;
    connect(image->m_manager, &HBWebImageManager::signal_getImage, [imgView, image](const QPixmap& map) {

        imgView->setPixmap(map);
        image->m_thread.quit();
//        image->deleteLater();
    });
    emit image->signalSetImage(urlStr);

}
