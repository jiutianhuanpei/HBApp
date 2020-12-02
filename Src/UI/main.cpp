#include "widget.h"
#include <QApplication>
#include "colorbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


//    ColorButton btn(ColorButton::Max);
//    btn.show();

    return a.exec();
}
