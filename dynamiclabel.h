#ifndef DYNAMICLABEL_H
#define DYNAMICLABEL_H

#include <QLabel>
class DynamicLabel : public QLabel
{
public:
    DynamicLabel();

    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void showEvent(QShowEvent* event);
    void closeEvent(QCloseEvent* event);
private:
    QPoint ptCenter,ptCenterNew;
    bool InitSign;
    bool ChangeDeltaValue;
    int r;
    int deltaX,deltaY;
    qreal deltaInterval;
    int m_pTimerID;
};

#endif // DYNAMICLABEL_H
