#ifndef CENTRALWGT_H
#define CENTRALWGT_H

#include <QWidget>
#include "qcustomplotex.h"
#include <QTimer>
#include "bass.h"
class CentralWgt : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWgt(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

private:
    QCustomPlotEx* m_customPlot;
    QCustomPlotEx* customPlot;

    QCPItemText *m_testText;
    QCPItemText *m_testText1;

    QTimer m_pTimer;
    QCPGraph *pGraph;

    struct SCommonParamSS
    {
        HSTREAM hs;//数据流变量
        float Data[100000];
        int len;//流媒体总的时间的长度
    };

    SCommonParamSS g_sCommParaSS;

    float FFTData[5120],FFTDataCurve[5120];
    int FFTPeacks[5120],FFTFallOff[5120],FFTPeacksCurve[5120],FFTFallOffCurve[5120];

    QCustomPlotEx* get_realtime_plot();
    QCustomPlotEx* get_water_fall_plot();
    void refresh_water_fall(double data[1024]);
    QCPColorScale *colorScale;
    QCPColorMap *colorMap;
    QCPColorMap *colorMap1;

    QCPMarginGroup *marginGroup;
signals:

public slots:
    void slot_real_data();

    void xAxisChanged(QCPRange range);
    void yAxisChanged(QCPRange range);
};

#endif // CENTRALWGT_H
