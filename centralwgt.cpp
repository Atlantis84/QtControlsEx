#include "centralwgt.h"
#include <QPainter>
#include "centralmainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include "basswgt.h"
#include "leftwidget.h"
#include "dynamiclabel.h"
CentralWgt::CentralWgt(QWidget *parent) : QWidget(parent)
{
    m_customPlot = nullptr;
    customPlot = nullptr;
    colorMap = nullptr;
    colorMap1 = nullptr;

    QVBoxLayout* vAll = new QVBoxLayout();
    QHBoxLayout* hBox1 = new QHBoxLayout();
    QHBoxLayout* hBox2 = new QHBoxLayout();
    QHBoxLayout* hBox3 = new QHBoxLayout();
    QHBoxLayout* hBox4 = new QHBoxLayout();

    BassWgt* bassWgt = new BassWgt();
    QWidget* bassWgt1 = new QWidget();
    LeftWidget* lftWgt = new LeftWidget();
    DynamicLabel* dynamicLabel = new DynamicLabel();
//    hBox1->addWidget(bassWgt);
//    hBox3->addWidget(lftWgt);
//    hBox3->addWidget(dynamicLabel);
//    vAll->addLayout(hBox1);
//    vAll->addLayout(hBox3);
//    this->setLayout(vAll);

    hBox2->addWidget(get_realtime_plot());
    hBox4->addWidget(get_water_fall_plot());
    vAll->addLayout(hBox2);
    vAll->addLayout(hBox4);
    connect(&m_pTimer,SIGNAL(timeout()),this,SLOT(slot_real_data()));
    m_pTimer.start(100);
    this->setLayout(vAll);
}

void CentralWgt::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
//    painter.fillRect(this->rect(),QBrush(QColor(255,0,0,100)));

}

QCustomPlotEx *CentralWgt::get_realtime_plot()
{
    if(m_customPlot == nullptr)
    {
        m_customPlot = new QCustomPlotEx();

        m_customPlot->setBackground(QBrush(QColor(100,25,55)));

        m_customPlot->xAxis->setBasePen(QPen(QColor(255,255,255)));
        m_customPlot->xAxis->setTickPen(QPen(QColor(255,255,255)));
        m_customPlot->xAxis->setSubTickPen(QPen(QColor(255,255,255)));
        m_customPlot->xAxis->setLabelColor(QColor(255,255,255));
        m_customPlot->xAxis->setTickLabelColor(QColor(255,255,255));

        m_customPlot->yAxis->setBasePen(QPen(QColor(255,255,255)));
        m_customPlot->yAxis->setTickPen(QPen(QColor(255,255,255)));
        m_customPlot->yAxis->setSubTickPen(QPen(QColor(255,255,255)));
        m_customPlot->yAxis->setLabelColor(QColor(255,255,255));
        m_customPlot->yAxis->setTickLabelColor(QColor(255,255,255));
    }
    else
        return m_customPlot;

    if (!BASS_Init(-1,44100,0,(HWND)this->winId(),NULL))
        qDebug()<<u8"初始化设备失败!";

    if (HIWORD(BASS_GetVersion())!=BASSVERSION)
        qDebug()<<u8"Bass.dll版本不合适!";

    if (BASS_ChannelIsActive(g_sCommParaSS.hs)==BASS_ACTIVE_PLAYING)
            BASS_ChannelStop(g_sCommParaSS.hs);

//    HSTREAM hs1;//临时数据流变量
//    double time;//获取音频流媒体的播放总时间
    BASS_StreamFree(g_sCommParaSS.hs);
    const char file[] = "E:/1.mp3";

    if (!(g_sCommParaSS.hs = BASS_StreamCreateFile(FALSE,file,0,0,0))) {
        qDebug()<<u8"不能加载音频文件!";
    }

    if(BASS_ChannelPlay(g_sCommParaSS.hs,FALSE))
        qDebug()<<u8"播放成功!";
    else
        qDebug()<<u8"播放失败!";

    pGraph = m_customPlot->addGraph();
    m_customPlot->graph()->setPen(QColor(0,255,0));
    m_customPlot->showSS(true);

//    connect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_customPlot->xAxis2, SLOT(setRange(QCPRange)));
//    connect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_customPlot->yAxis2, SLOT(setRange(QCPRange)));

    m_customPlot->xAxis->setRange(0.0,1024.0);
    m_customPlot->yAxis->setRange(-200.0,200.0);
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(m_customPlot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(xAxisChanged(QCPRange)));

    return m_customPlot;
}

QCustomPlotEx *CentralWgt::get_water_fall_plot()
{
//    demoName = "Color Map Demo";
    if(customPlot == nullptr)
    {
        customPlot = new QCustomPlotEx();
        customPlot->setBackground(QBrush(QColor(100,25,55)));

        customPlot->xAxis->setBasePen(QPen(QColor(255,255,255)));
        customPlot->xAxis->setTickPen(QPen(QColor(255,255,255)));
        customPlot->xAxis->setSubTickPen(QPen(QColor(255,255,255)));
        customPlot->xAxis->setLabelColor(QColor(255,255,255));
        customPlot->xAxis->setTickLabelColor(QColor(255,255,255));

        customPlot->yAxis->setBasePen(QPen(QColor(255,255,255)));
        customPlot->yAxis->setTickPen(QPen(QColor(255,255,255)));
        customPlot->yAxis->setSubTickPen(QPen(QColor(255,255,255)));
        customPlot->yAxis->setLabelColor(QColor(255,255,255));
        customPlot->yAxis->setTickLabelColor(QColor(255,255,255));
    }
    else
        return customPlot;

    if(colorMap == nullptr)
        colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);

    if(colorMap1 == nullptr)
        colorMap1 = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);

//    customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect

    // configure axis rect:
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x");
    customPlot->xAxis->setRange(0,1024);
    customPlot->yAxis->setLabel("y");

    int nx = 1024;
    int ny = 250;
    colorMap->data()->setSize(nx, ny);
    colorMap->data()->setRange(QCPRange(0,1024), QCPRange(0,5));

    colorMap1->data()->setSize(nx, ny);
    colorMap1->data()->setRange(QCPRange(0,1024), QCPRange(5,10));
    return customPlot;
}

double count = 0.0;
int tmpCount = 0;
bool changeSign = false;
int intervalCount = 0;
void CentralWgt::refresh_water_fall(double data[1024])
{
    tmpCount++;
    count+=0.02;
    int nx = 1024;
    double x, y;
    if((tmpCount % 250) == 0)
    {
        intervalCount++;
        tmpCount = 0;

        if((intervalCount%2) == 0)
        {
            colorMap1->data()->clear();
            colorMap1->data()->setSize(1024,250);
            colorMap1->data()->setRange(QCPRange(0,1024), QCPRange(10+5*(intervalCount-1),10+5*intervalCount));
        }
        else
        {
            colorMap->data()->clear();
            colorMap->data()->setSize(1024,250);
            colorMap->data()->setRange(QCPRange(0,1024), QCPRange(10+5*(intervalCount-1),10+5*intervalCount));
        }
    }

    if((intervalCount % 2) == 0)
    {
        for (int xIndex=0; xIndex<nx; ++xIndex)
        {
            colorMap1->data()->cellToCoord(xIndex, tmpCount, &x, &y);
            colorMap1->data()->setCell(xIndex, tmpCount, data[xIndex]);
        }
        colorMap1->setGradient(QCPColorGradient::gpJet);
        colorMap1->rescaleDataRange();
    }
    else{
        for (int xIndex=0; xIndex<nx; ++xIndex)
        {
            colorMap->data()->cellToCoord(xIndex, tmpCount, &x, &y);
            colorMap->data()->setCell(xIndex, tmpCount, data[xIndex]);
        }
        colorMap->setGradient(QCPColorGradient::gpJet);
        colorMap->rescaleDataRange();
    }

    // rescale the key (x) and value (y) axes so the whole color map is visible:
//    customPlot->rescaleAxes();
    customPlot->yAxis->setRange(count,count+5);

    customPlot->replot();
}

void CentralWgt::slot_real_data()
{
    // generate some data:
    int nCount = 5120;

    QVector<double> x(nCount), y0(nCount), y1(nCount); // initialize with entries 0..100

    double tmpData[1024];
    BASS_ChannelGetData(g_sCommParaSS.hs,&FFTData,BASS_DATA_FFT1024);
    for(int i=0;i<1024;i++)
    {
//        srand(QTime(0,0,0).msecsTo(QTime::currentTime()));
//        double test =rand()%255;
//        tmpData[i] = test;
        if(i<512)
        {
            tmpData[i] = FFTData[511 - i];
            double aa = fabs(tmpData[i])*5000.0;
            if(aa > 200.0)
                tmpData[i] = 200.0 / 5000.00;

        }
        else
        {
            tmpData[i] = FFTData[i-511];
            double aa = fabs(tmpData[i])*5000.0;
            if(aa > 200.0)
                tmpData[i] = 200.0 / 5000.00;
        }
    }

    for (int i = -512; i < 512; i++)
    {
        x[i+512] = i;
        y1[i+512] = static_cast<double>(fabs(tmpData[i+512])*5000) ;
    }

    pGraph->setData(x,y1);
    m_customPlot->replot();

    refresh_water_fall(tmpData);
}

void CentralWgt::xAxisChanged(QCPRange range)
{
    customPlot->xAxis->setRange(range);
    customPlot->replot();
}

void CentralWgt::yAxisChanged(QCPRange range)
{

}
