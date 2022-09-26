#include "bassstwgt.h"
#include <QPainter>
#include <QDebug>
BassStWgt::BassStWgt(QWidget *parent) : QWidget(parent)
{
    if (BASS_ChannelIsActive(g_sCommPara.hs)==BASS_ACTIVE_PLAYING)
            BASS_ChannelStop(g_sCommPara.hs);

    HSTREAM hs1;//��ʱ����������
    double time;//��ȡ��Ƶ��ý��Ĳ�����ʱ��
    BASS_StreamFree(g_sCommPara.hs);
    const char file[] = "E:/1.mp3";

    if (!(g_sCommPara.hs = BASS_StreamCreateFile(FALSE,file,0,0,0))
            && !(g_sCommPara.hs = BASS_MusicLoad(FALSE,file,0,0,BASS_MUSIC_RAMPS|BASS_MUSIC_POSRESET|BASS_MUSIC_PRESCAN,1))) {
        qDebug()<<u8"���ܼ�����Ƶ�ļ�!";
    }

    hs1 = BASS_StreamCreateFile(FALSE,file,0,0,BASS_STREAM_DECODE);
    time = BASS_ChannelBytes2Seconds(hs1,BASS_ChannelGetLength(g_sCommPara.hs,BASS_POS_BYTE));
    int count = static_cast<int>(1200/time);//���ݿؼ��Ŀ�Ⱦ���ȡ�����ε�ʱ����
    for (int i=0;i<static_cast<int>(time*count+1);i++)
        g_sCommPara.Data[i] = BASS_ChannelGetLevel(hs1);

    BASS_StreamFree(hs1);
    g_sCommPara.len = static_cast<int>(time*count+1);
    BASS_ChannelPlay(g_sCommPara.hs,FALSE);
//    this->startTimer(100);
}
int count1=0;
void BassStWgt::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(count1 >= 255)
        count1 = 0;
    count1+=5;
    QPainter painter(this);
    QRect rtStatic(0,0,this->width(),this->height());
//    painter.fillRect(rtStatic,QBrush(QColor(0,200,0,100)));
    painter.fillRect(rtStatic,QBrush(QColor(255,0,0,100),Qt::DiagCrossPattern));
    painter.setPen(QColor(0,255,0));
    int height = this->height();
    for (int i = 0; i < g_sCommPara.len; i++)
    {
        int L,R;
        L = LOWORD(g_sCommPara.Data[i]);
        R = HIWORD(g_sCommPara.Data[i]);
        painter.drawLine(i,height/2-L/500,i,height/2+R/500);
    }

//    QRect rtDynamic(0,this->height()/2,this->width(),this->height()/2);
//    painter.fillRect(rtDynamic,QBrush(QColor(255,count1,0)));
}

void BassStWgt::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    this->repaint();
}
