#include "hbtreeview.h"
#include <QPalette>
#include <QList>
#include <QDebug>

HBTreeView::HBTreeView(QWidget *parent) : QTreeView(parent)
{
    QStringList headers;
    headers << "First" << "Second";
    //headers << "第一个" << "第二个";
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

void HBTreeView::setData()
{


    QList<QVariant> list;
    list << "aaa";

    model->appendData(list, QModelIndex());


}
