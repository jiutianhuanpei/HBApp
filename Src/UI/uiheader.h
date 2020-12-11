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


enum MousePoint {
//    None = -1,

//    Left = 1 << 0,
//    Top = 1 << 1,
//    Right = 1 << 2,
//    Bottom = 1 << 3,

//    Moveside = 1 << 4,
//    Inside = 1 << 5,
//    OutSide = 1 << 6,

//    LeftTop = Left | Top,
//    RightTop = Right | Top,
//    RightBottom = Right | Bottom,
//    LeftBottom = Left | Bottom,


    Out = 0,
    Low = 1,
    Mid = 3,
    Hight = 5,

    //鼠标位置
    LeftTop = Low << Low,
    Top = Mid << Low,
    RightTop = Hight << Low,

    Left = Low << Mid,
    CenterSide = Mid << Mid,
    MoveSide = CenterSide << 1,
    Right = Hight << Mid,

    LeftBottom = Low << Hight,
    Bottom = Mid << Hight,
    RightBottom = Hight << Hight,


//    LeftTop,
//    Top,
//    RightTop,
//    Right,
//    RightBottom,
//    Bottom,
//    LeftBottom,
//    Left,
//    Inside,
//    Outside,
//    Moveside
};



#endif // UIHEADER_H
