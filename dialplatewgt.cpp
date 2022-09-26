#include "dialplatewgt.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
DialPlateWgt::DialPlateWgt(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    resize(1920,1080);
}

void DialPlateWgt::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(QColor(255,0,0,255)));
    painter.setFont(QFont("KaiTi",10,20,false));
    QPoint tmpPtCenter(this->rect().width()/2,this->rect().height()/2);
    int tmpCR = (this->height() - 50)/2;
    painter.translate(tmpPtCenter.x(),tmpPtCenter.y());

    for(int i=0;i<360;i++)
    {
        QString strPaint = QString("%1").arg(i);
        int textWidth = fontMetrics().width(strPaint.at(0));
        int textHeight = fontMetrics().height();

        if(i%30 == 0)
        {
            QRect textRect(-textWidth / 2, -(tmpCR + textHeight / 2), textWidth+15, textHeight + 15);
            painter.drawText(textRect, Qt::AlignCenter, strPaint);
            painter.rotate(30);
        }
    }
    return;

    painter.setRenderHint(QPainter::Antialiasing, true);
    //radiation gradient color
    QRadialGradient radialGradient(this->width()/2,this->height()/2,this->width()/2,this->width()/2,this->height()/2);
    radialGradient.setColorAt(0,QColor(255,0,0,100));
    radialGradient.setColorAt(1.0,Qt::black);
    painter.fillRect(this->rect(),QBrush(radialGradient));

    int R,rInterval,tmpR,boldR,arcR;
    arcR =0;
    qreal scaleRin,scaleRin_Out,scaleRout;
    ptCenter.setX(this->width()/2);
    ptCenter.setY(this->height()/2);
    if(this->width()>= this->height())
    {
        R = this->height()/2.1;
        tmpR = this->height()/2;
        boldR = this->height()/2.05;
        arcR = this->height()/1.9;

        scaleRin = (qreal)this->height()/2.1;
        scaleRin_Out = (qreal)this->height()/2.06;
        scaleRout = (qreal)this->height()/2.02;
    }
    else
    {
        R = this->width()/2.1;
        tmpR = this->width()/2;
        boldR = this->width()/2.05;

        scaleRin = (qreal)this->width()/2.1;
        scaleRin_Out = (qreal)this->width()/2.06;
        scaleRout = (qreal)this->width()/2.02;
    }

    rInterval = R/9;
    painter.setPen(QColor(0,255,0,100));

    //draw circles
    painter.drawEllipse(ptCenter,tmpR,tmpR);
    for (int i=0; i<10;i++ )
        painter.drawEllipse(ptCenter,i*rInterval,i*rInterval);

    //draw radation lines
    for (int i=0; i<36;i++ ) {
        QPointF tmpPt1((qreal)ptCenter.x(),(qreal)ptCenter.y());
        QPointF tmpPt2((qreal)ptCenter.x()+(qreal)(9*rInterval)*cos(i*10*M_PI/180.0),(qreal)ptCenter.y()-(qreal)(9*rInterval)*sin(i*10*M_PI/180.0));
        if(i%3 == 0)
            painter.drawLine(tmpPt1,tmpPt2);
    }

    //draw half-transparent ring band
    painter.setPen(QPen(QBrush(QColor(0,255,0,20)),(qreal)(tmpR-9*rInterval)));
    painter.drawEllipse(ptCenter,boldR,boldR);

    //draw half-transparent ears
//    if(arcR != 0)
//    {
//        painter.setPen(QPen(QBrush(QColor(0,255,0,30)),(qreal)(arcR-tmpR)));
//        QRect tmpRt;
//        tmpRt.setLeft(ptCenter.x()-arcR);
//        tmpRt.setBottom(ptCenter.y() - arcR);
//        tmpRt.setTop(ptCenter.y()+arcR);
//        tmpRt.setRight(ptCenter.x()+arcR);
//        painter.drawArc(tmpRt,135*16,90*16);
//        painter.drawArc(tmpRt,45*16,-90*16);
//    }

    //draw linear-gradient vertical column
//    if(((qreal)(this->width())/(qreal)(this->height())) > 1.3)
//    {
//        QLinearGradient Linear(this->width()/20*19,this->height()/10*3,
//                               this->width()/20*19,this->height()/10*7);//垂直渐变,x1=x2为垂直渐变
//        Linear.setColorAt(1,QColor(255,0,0,100));
//        Linear.setColorAt(0,QColor(0,255,0,100));
//        painter.fillRect(QRectF(this->width()/20*19,this->height()/10,
//                                this->width()/40,this->height()/10*7),QBrush(Linear));
//        painter.fillRect(QRectF(this->width()/20*19,this->height()/10,
//                                this->width()/40,this->height()/10*7),QBrush(Qt::DiagCrossPattern));
//    }

    painter.setPen(QColor(0,255,0,100));//reset pen
    //draw scale lines
    for (int i=0; i<360;i++)
    {
        if(i%2 == 0)
        {
            if(i%30 == 0)
            {
                QPointF tmpPt1((qreal)ptCenter.x()+(qreal)scaleRin*cos(i*M_PI/180.0),(qreal)ptCenter.y()-(qreal)scaleRin*sin(i*M_PI/180.0));
                QPointF tmpPt2((qreal)ptCenter.x()+(qreal)scaleRout*cos(i*M_PI/180.0),(qreal)ptCenter.y()-(qreal)scaleRout*sin(i*M_PI/180.0));
                painter.drawLine(tmpPt1,tmpPt2);
//                painter.save();
//                painter.translate(ptCenter.x()-R,ptCenter.y()+R);
//                painter.rotate(i);
//                painter.drawText(tmpPt2.x(),tmpPt2.y(),QString("%1").arg(i));
//                painter.restore();
            }
            else {
                QPointF tmpPt1((qreal)ptCenter.x()+(qreal)scaleRin*cos(i*M_PI/180.0),(qreal)ptCenter.y()-(qreal)scaleRin*sin(i*M_PI/180.0));
                QPointF tmpPt2((qreal)ptCenter.x()+(qreal)scaleRin_Out*cos(i*M_PI/180.0),(qreal)ptCenter.y()-(qreal)scaleRin_Out*sin(i*M_PI/180.0));
                painter.drawLine(tmpPt1,tmpPt2);
            }
        }

    }

    QRect rect(ptCenter.x()-9*rInterval, ptCenter.y()-9*rInterval, 2*9*rInterval,2*9*rInterval);
    for (int i=119;i>=0;i-- ) {
        QPainterPath path;
        path.moveTo(ptCenter);//move to center of the circle
        path.arcTo(rect,delayValue +i,1);
        painter.fillPath(path,QBrush(QColor(0,255,0,119-i)));
    }
}
