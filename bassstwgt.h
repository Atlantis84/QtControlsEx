#ifndef BASSSTWGT_H
#define BASSSTWGT_H

#include <QWidget>
#include "bass.h"
struct SCommonParam
{
    HSTREAM hs;//����������
    float Data[100000];
    int len;//��ý���ܵ�ʱ��ĳ���
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
