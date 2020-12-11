#ifndef HBWEBIMAGE_H
#define HBWEBIMAGE_H

#include <QObject>
#include <QThread>
#include "hbwebimagemanager.h"
#include <QLabel>

class HBWebImage : public QObject
{
    Q_OBJECT
public:
    explicit HBWebImage(QObject *parent = nullptr);
    ~HBWebImage();

    static void setImage(const QString urlStr, QLabel* imgView);


    HBWebImageManager *imageManager() { return m_manager;};

signals:
    void signalSetImage(const QString);
    void signalBindImgView(QLabel*);


private:
    QThread m_thread;
    HBWebImageManager *m_manager;

};

#endif // HBWEBIMAGE_H
