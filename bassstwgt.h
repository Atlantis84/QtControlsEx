#ifndef BASSSTWGT_H
#define BASSSTWGT_H

#include <QWidget>
#include "bass.h"
struct SCommonParam
{
    HSTREAM hs;//数据流变量
    float Data[100000];
    int len;//流媒体总的时间的长度
};

class BassStWgt : public QWidget
{
    Q_OBJECT
public:
    explicit BassStWgt(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    SCommonParam g_sCommPara;

signals:

public slots:
};

#endif // BASSSTWGT_H
