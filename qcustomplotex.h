#ifndef QCUSTOMPLOTEX_H
#define QCUSTOMPLOTEX_H
#include "qcustomplot.h"
#include <QObject>
#include <QList>
#include "mousetracer.h"
#include <QAction>

class QCustomPlotEx : public QCustomPlot
{
    Q_OBJECT
public:
    QCustomPlotEx(QWidget *parent = 0);
    void showSS(bool show);
    bool isShowTracer(){return m_isShowTracer;}

protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseWheel(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool m_isShowTracer;//是否显示追踪器（鼠标在图中移动，显示对应的值）
    MouseTracer *m_xTracer;//x轴
    MouseTracer *m_yTracer;//y轴
    QList<MouseTracer *> m_dataTracers;//
    MouseTraceLine  *m_lineTracer;//直线

    QList<MouseTracer*> m_xMarkerList;//x axis maker
    QList<QAction*> lstAction;
    QList<QCPItemText*> lstText;

public slots:
    void slot_menu_click(int id);

};

#endif // QCUSTOMPLOTEX_H
