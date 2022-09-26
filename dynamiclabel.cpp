#include "dynamiclabel.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <math.h>
DynamicLabel::DynamicLabel()
{
    InitSign = false;
    ChangeDeltaValue = false;
    deltaInterval = 0.0;
}

void DynamicLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    QLinearGradient Linear(0,this->height(),this->width(),this->height());//垂直渐变,x1=x2为垂直渐变
    Linear.setColorAt(0,QColor(0,255,0,50));
    Linear.setColorAt(0.5,QColor(255,0,0,80));
    Linear.setColorAt(1,QColor(0,255,0,50));
    painter.fillRect(this->rect(),QBrush(Linear));

    painter.save();
    if(InitSign == false)
        painter.translate(ptCenter);
    else
    {
        if(ChangeDeltaValue == false)
        {
            int seed = QDateTime::currentDateTime().time().msec();
            srand(static_cast<unsigned int>(seed));
            ptCenterNew.setX((rand()%(this->width()-51))+51);
            ptCenterNew.setY((rand()%(this->height()-51))+51);
            ChangeDeltaValue = true;
        }

        deltaX = ptCenter.x()-ptCenterNew.x();
        deltaY = ptCenter.y()-ptCenterNew.y();

        qreal xx = static_cast<qreal>(deltaX)/sqrt(pow(deltaX,2)+pow(deltaY,2))*deltaInterval;
        qreal yy = static_cast<qreal>(deltaY)/sqrt(pow(deltaY,2)+pow(deltaX,2))*deltaInterval;

        painter.translate(ptCenter.x()-xx,ptCenter.y()-yy);
        if(((ptCenter.x()-xx) <= 51) || ((ptCenter.x()-xx) >= (this->width()-51))||((ptCenter.y()-yy)<=51)||((ptCenter.y()-yy)>=this->height()-51))
        {
            ptCenter.setX(static_cast<int>(ptCenter.x()-xx));
            ptCenter.setY(static_cast<int>(ptCenter.y()-yy));
            deltaInterval = 0.0;
            ChangeDeltaValue = false;
        }
    }
    for (int i=0;i<51;i++) {
        painter.setPen(QPen(QColor(255,0,0,255-i*5),5));
        painter.drawEllipse(QRect(-i,-i,2*i,2*i));
    }
    painter.restore();

//    painter.fillRect(this->rect(),QBrush(QColor(255,255,255,50),Qt::DiagCrossPattern));
}

void DynamicLabel::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if(InitSign == false)
    {
        ptCenter.setX(this->width()/2);
        ptCenter.setY(this->height()/2);
    }
    this->repaint();

    deltaInterval+=2.0;
    InitSign = true;
//    this->killTimer(this->m_pTimerID);
}

void DynamicLabel::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    this->m_pTimerID = this->startTimer(10);
}

void DynamicLabel::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->killTimer(this->m_pTimerID);
}
