#include "gradientcolumnwgt.h"
#include <QPainter>

GradientColumnWgt* GradientColumnWgt::m_pGradientColumnWgt=nullptr;

static int TestValue;
GradientColumnWgt::GradientColumnWgt(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags() | Qt::Widget);
    setAttribute(Qt::WA_TranslucentBackground, true);
    this->setFixedHeight(200);
    this->setFixedWidth(60);

    TestValue = 0;
    startTimer(1000);
}

void GradientColumnWgt::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rt(this->width()/2 -10,this->height()-TestValue,20,TestValue);
    QRect rt1(this->width()/2 -10,0,20,this->height());
    QLinearGradient Linear(rt.width()/20*19,rt.height()/10*3,
                           rt.width()/20*19,rt.height()/10*7);//垂直渐变,x1=x2为垂直渐变
    Linear.setColorAt(1,QColor(150,0,0));
    Linear.setColorAt(0,QColor(0,150,0));

    QPainterPath path,path1;
    path.addRoundedRect(rt,50,10,Qt::RelativeSize);
    path1.addRoundedRect(rt1,50,10,Qt::RelativeSize);
    painter.fillPath(path1,QBrush(QColor(255,255,255,100)));
    painter.fillPath(path,QBrush(Linear));
}

void GradientColumnWgt::timerEvent(QTimerEvent *event)
{
    if(TestValue == 200)
        TestValue = 0;
    TestValue+=10;
    this->repaint();
}
