#include "pathtohit.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
PathToHit::PathToHit(QWidget *parent) : QWidget(parent)
{
    pathToPaint = new QPainterPath();
}

void PathToHit::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    pathToPaint->addEllipse(this->rect());
    painter.drawPath(*pathToPaint);
}

void PathToHit::mouseMoveEvent(QMouseEvent *event)
{
    QPointF offsetPos = event->pos();
    if(pathToPaint->contains(offsetPos))
        qDebug()<<"in";
    else {
        qDebug()<<"out";
    }
}
