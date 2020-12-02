#include "hbwebview.h"
#include <QVBoxLayout>

HBWebView::HBWebView(QWidget *parent) : QWidget(parent)
{
    _InitializeWidgets();
}

HBWebView::~HBWebView()
{
//    if (webView)
//        delete webView;
}

void HBWebView::load(const QUrl& url)
{
    webView.load(url);
}

void HBWebView::_InitializeWidgets()
{

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

//    QWebEngineView webView;// = new QWebEngineView;
    layout->addWidget(&webView);

}
