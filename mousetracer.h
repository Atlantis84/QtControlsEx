#ifndef MOUSETRACER_H
#define MOUSETRACER_H

#include <QObject>
#include "qcustomplot.h"

class QCPItemTextEx:public QCPItemText
{
    Q_OBJECT
public:
  QCPItemTextEx(QCustomPlot *parentPlot);
  virtual ~QCPItemTextEx()Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  QCustomPlot *m_plot;
};

class MouseTracer : public QObject
{
    Q_OBJECT
public:

    enum TracerType
    {
        XAxisTracer=0,//依附在x轴上显示x值
        YAxisTracer=1,//依附在y轴上显示y值
        DataTracer=2,//在图中显示x,y值
        MouseMarker=3//固定游标
    };

    explicit MouseTracer(QCustomPlot *_plot, TracerType _type, QObject *parent = Q_NULLPTR);
    ~MouseTracer();

    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setText(const QString &text);
    void setLabelPen(const QPen &pen);
    void updatePosition(double xValue, double yValue);
    void setVisible(bool m_visible);

    //marker
    int getMarkerID(){return m_marker_id;}
    void setMarkerID(int id){if((id>0) && (id<6))m_marker_id=id;}
    void setXValue(qreal x){m_x_value = x;}
    void removeMarker();

protected:
    bool m_visible;//是否可见
    TracerType m_type;//类型
    QCustomPlot *m_plot;//图表
    QCPItemTracer *m_tracer;//跟踪的点
    QCPItemText *m_label;//显示的数值

    QCPItemTextEx *m_marker;
    int m_marker_id = -1;
    qreal m_x_value;
    QCPItemLine *m_arrow;//箭头

signals:

public slots:
};

class MouseTraceLine : public QObject
{
public:
    enum LineType
    {
        VerticalLine,//垂直线
        HorizonLine, //水平线
        Both//同时显示水平和垂直线
    };
    explicit MouseTraceLine(QCustomPlot *_plot, LineType _type = VerticalLine, QObject *parent = Q_NULLPTR);
    ~MouseTraceLine();
    void initLine();
    void updatePosition(double xValue, double yValue);

//    void addMarker(double xValue);

    void setVisible(bool vis)
    {
        if(m_lineV)
            m_lineV->setVisible(vis);
        if(m_lineH)
            m_lineH->setVisible(vis);
    }

protected:
    bool m_visible;//是否可见
    LineType m_type;//类型
    QCustomPlot *m_plot;//图表
    QCPItemStraightLine *m_lineV; //垂直线
    QCPItemStraightLine *m_lineH; //水平线
};
#endif // MOUSETRACER_H
