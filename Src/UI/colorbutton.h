#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QWidget>
#include <QMouseEvent>

class ColorButton : public QWidget
{
    Q_OBJECT
public:

    enum ButtonType {
        Close,
        Min,
        Max
    };

    explicit ColorButton(QWidget *parent = nullptr);

    void setType(ButtonType type);

signals:
    void signalDidClickedBtn();


protected:
    void mousePressEvent(QMouseEvent *event);

};

#endif // COLORBUTTON_H
