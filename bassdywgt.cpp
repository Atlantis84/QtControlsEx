#include "bassdywgt.h"
#include <QPainter>
#include "bass.h"
#include <QDebug>

struct SCommonParamS
{
    HSTREAM hs;//数据流变量
    float Data[100000];
    int len;//流媒体总的时间的长度
};

static SCommonParamS g_sCommParaS;
BassDyWgt::BassDyWgt(QWidget *parent) : QWidget(parent)
{
    if (BASS_ChannelIsActive(g_sCommParaS.hs)==BASS_ACTIVE_PLAYING)
            BASS_ChannelStop(g_sCommParaS.hs);

//    HSTREAM hs1;//临时数据流变量
//    double time;//获取音频流媒体的播放总时间
    BASS_StreamFree(g_sCommParaS.hs);
    const char file[] = "E:/1.mp3";

    if (!(g_sCommParaS.hs = BASS_StreamCreateFile(FALSE,file,0,0,0))) {
        qDebug()<<u8"不能加载音频文件!";
    }

    BASS_ChannelPlay(g_sCommParaS.hs,FALSE);
    this->startTimer(100);
}

void BassDyWgt::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(this->rect(),QBrush(QColor(180,0,0,100)));
    painter.setPen(QPen(QColor(0,255,0),8));
    int m_pColumHeight = this->height();
    BASS_ChannelGetData(g_sCommParaS.hs,&FFTData,BASS_DATA_FFT1024);
    for (int i = 0; i < 512; i++)
    {
        int di = 0;
        di = static_cast<int>(fabs(FFTData[i])*500) ;

        if (di>m_pColumHeight) di = m_pColumHeight;

        if (di>=FFTPeacks[i]) FFTPeacks[i] = di;
        else FFTPeacks[i] = FFTPeacks[i]-1;

        if (di>=FFTFallOff[i]) FFTFallOff[i] = di;
        else FFTFallOff[i] = FFTFallOff[i]-3;

        if (fabs(m_pColumHeight-FFTPeacks[i])>m_pColumHeight) FFTPeacks[i] = 0;
        if (fabs(m_pColumHeight-FFTFallOff[i])>m_pColumHeight) FFTFallOff[i] = 0;
        painter.drawLine(i*9,m_pColumHeight-FFTFallOff[i],i*9,m_pColumHeight);
    }

}

void BassDyWgt::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    this->repaint();
}
