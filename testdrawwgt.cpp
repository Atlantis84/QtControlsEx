#include "testdrawwgt.h"
#include <QPainter>
TestDrawWgt::TestDrawWgt(QWidget *parent) : QWidget(parent)
{
    resize(1200,1000);
}

void TestDrawWgt::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(255,0,0,100)));
//    QRect rt(0,0,200,200);
//    painter.translate(200,200);
//    painter.rotate(10);
//    painter.fillRect(rt,QBrush(QColor(255,0,0,100)));

    QPainterPath path,path1;
    path.setFillRule(Qt::OddEvenFill);
    path1.setFillRule(Qt::OddEvenFill);
//    path.moveTo(80, 320);
//    path.cubicTo(280, 80, 280, 80, 480, 320);
//    painter.setPen(QPen(Qt::red, 8));
//    painter.fillPath(path,QBrush(QColor(255,0,0,100)));

    QPolygonF tmpPolygon;//图形叠加时，如果角度为正值时，叠加消失效果带边框线，负角度时边框线消失，原因不知
    tmpPolygon<<QPointF(200.0,100.0)<<QPointF(100.0,200.0)<<QPointF(200.0,300.0)<<QPointF(300.0,200.0);
    path.addPolygon(tmpPolygon);
    path.moveTo(200.0,100.0);
    path.arcTo(0.0,0.0,200.0,200.0,0.0,-90.0);
    path.moveTo(100.0,200.0);
    path.arcTo(0.0,200.0,200.0,200.0,90.0,-90.0);
    path.moveTo(200.0,300.0);
    path.arcTo(200.0,200.0,200.0,200.0,180.0,-90.0);
    path.moveTo(300.0,200.0);
    path.arcTo(200.0,0.0,200.0,200.0,270.0,-90.0);
//    painter.drawPath(path);
    painter.fillPath(path,QBrush(QColor(255,0,0,150)));

//    QPolygonF plyg1,plyg2;
//    plyg1<<QPointF(10,10)<<QPointF(110,10)<<QPointF(110,110)<<QPointF(10,110);
//    plyg2<<QPointF(20,20)<<QPointF(100,20)<<QPointF(100,100)<<QPointF(20,100);
//    path.addPolygon(plyg1);
//    path.addPolygon(plyg2);
//    painter.fillPath(path,QBrush(QColor(255,0,0,100)));

}
