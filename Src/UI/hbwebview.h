#ifndef HBWEBVIEW_H
#define HBWEBVIEW_H

#include <QWidget>
#include <QtWebEngineWidgets>

class HBWebView : public QWidget
{
    Q_OBJECT
public:
    explicit HBWebView(QWidget *parent = nullptr);
    ~HBWebView();

    void load(const QUrl& url);

signals:

public slots:

private:
    void _InitializeWidgets();

private:
    QWebEngineView webView;

};

#endif // HBWEBVIEW_H
