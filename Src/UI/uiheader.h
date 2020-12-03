#ifndef UIHEADER_H
#define UIHEADER_H

#include <QWidget>

enum MenuIndex {
    BigScreen,
    Monitor,
    PersonMgr,
    Poll,
    Map,
    Web
};

enum WindowZoom {
    Close,
    Min,
    Max
};


enum AppBorderDirection {
    LeftTop,
    Top,
    RightTop,
    Right,
    RightBottom,
    Bottom,
    LeftBottom,
    Left,
    Inside,
    Outside,
    Moveside
};



#endif // UIHEADER_H
