#include "hbtreeview.h"
#include <QPalette>

HBTreeView::HBTreeView(QWidget *parent) : QTreeView(parent)
{
    QStringList headers;
    headers << "aaaa" << "bbbbb";
//    headers
//        << QString::fromLocal8Bit("组织名称")
//        << QString::fromLocal8Bit("组织编号")
//        << QString::fromLocal8Bit("在线数")
//        << QString::fromLocal8Bit("总数")
//        << QString::fromLocal8Bit("是否有子节点")
//        << QString::fromLocal8Bit("经度")
//        << QString::fromLocal8Bit("纬度")
//        << QString::fromLocal8Bit("类型")
//        << QString::fromLocal8Bit("需要获取");

    model = new HBTreeModel(headers);
    setModel(model);

}
