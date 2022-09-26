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
        XAxisTracer=0,//������x������ʾxֵ
        YAxisTracer=1,//������y������ʾyֵ
        DataTracer=2,//��ͼ����ʾx,yֵ
        MouseMarker=3//�̶��α�
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
    bool m_visible;//�Ƿ�ɼ�
    TracerType m_type;//����
    QCustomPlot *m_plot;//ͼ��
    QCPItemTracer *m_tracer;//���ٵĵ�
    QCPItemText *m_label;//��ʾ����ֵ

    QCPItemTextEx *m_marker;
    int m_marker_id = -1;
    qreal m_x_value;
    QCPItemLine *m_arrow;//��ͷ

signals:

public slots:
};

class MouseTraceLine : public QObject
{
public:
    enum LineType
    {
        VerticalLine,//��ֱ��
        HorizonLine, //ˮƽ��
        Both//ͬʱ��ʾˮƽ�ʹ�ֱ��
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
    bool m_visible;//�Ƿ�ɼ�
    LineType m_type;//����
    QCustomPlot *m_plot;//ͼ��
    QCPItemStraightLine *m_lineV; //��ֱ��
    QCPItemStraightLine *m_lineH; //ˮƽ��
};
#endif // MOUSETRACER_H
