#include "leftwidget.h"
#include <QPainter>
#include <QWheelEvent>
LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{
    DelayValue = 0;
//    this->startTimer(100);
}

void LeftWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QLinearGradient Linear(this->width()/20*18,this->height()/10,
                           this->width()/20*18,this->height()/10*8);//垂直渐变,x1=x2为垂直渐变
    Linear.setColorAt(1,QColor(20,20,20));
    Linear.setColorAt(0.55,QColor(255,255,255));
    Linear.setColorAt(0,QColor(20,20,20));
    painter.fillRect(QRectF(this->width()/20,this->height()/10,
                            this->width()/20*18,this->height()/10*8),QBrush(Linear));

    painter.setPen(QPen(QColor(255,0,0),3));
    painter.drawLine(this->width()/20,this->height()/2,this->width()/20*19,this->height()/2);
//    painter.fillRect(QRectF(this->width()/20,this->height()/10,
//                            this->width()/20*18,this->height()/10*8),QBrush(Qt::Dense6Pattern));

    int fullScale = this->height()/10*8;
    int intervalCount = fullScale/5;
    for (int i=-intervalCount;i<intervalCount;i++) {
        painter.setPen(QPen(QColor(0,0,0),2));
        painter.setFont(QFont("宋体",12,QFont::Light,false));
        if(i%5==0)
        {
            painter.drawLine(this->width()/20,this->height()/10+i*5+DelayValue,this->width()/20+20,this->height()/10+i*5+DelayValue);
            painter.drawLine(this->width()/20*19,this->height()/10+i*5+DelayValue,this->width()/20*19-20,this->height()/10+i*5+DelayValue);
            QRectF rtText(this->width()/20,this->height()/10+i*5-10+DelayValue,this->width()/20*18,20);
            painter.drawText(rtText,Qt::AlignHCenter | Qt::AlignVCenter,QString("%1").arg(i)+"%");
        }
        else
        {
            painter.drawLine(this->width()/20,this->height()/10+i*5+DelayValue,this->width()/20+10,this->height()/10+i*5+DelayValue);
            painter.drawLine(this->width()/20*19,this->height()/10+i*5+DelayValue,this->width()/20*19-10,this->height()/10+i*5+DelayValue);
        }
    }

    painter.setPen(QPen(QColor(255,255,255,100),2));
    painter.drawRect(this->rect());

}

void LeftWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    DelayValue ++;
    QWidget::update();
}

void LeftWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        DelayValue+=3;
        this->repaint();
    }
    else
    {
        DelayValue-=3;
        this->repaint();
    }
}
