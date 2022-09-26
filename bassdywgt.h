#ifndef BASSDYWGT_H
#define BASSDYWGT_H

#include <QWidget>

class BassDyWgt : public QWidget
{
    Q_OBJECT
public:
    explicit BassDyWgt(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
private:
    float FFTData[512],FFTDataCurve[512];
    int FFTPeacks[512],FFTFallOff[512],FFTPeacksCurve[512],FFTFallOffCurve[512];

signals:

public slots:
};

#endif // BASSDYWGT_H
