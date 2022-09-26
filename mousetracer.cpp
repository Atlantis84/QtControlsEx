#include "mousetracer.h"

MouseTracer::MouseTracer(QCustomPlot *_plot, TracerType _type, QObject *parent)
    : QObject(parent),
      m_plot(_plot),
      m_type(_type)
{
    m_visible = true;
    m_tracer = Q_NULLPTR;// ���ٵĵ�
    m_label = Q_NULLPTR;// ��ʾ����ֵ
    m_arrow = Q_NULLPTR;// ��ͷ
    m_marker = Q_NULLPTR;
    if (m_plot)
    {
        QColor clrDefault(Qt::red);
        QBrush brushDefault(Qt::NoBrush);
        QPen penDefault(clrDefault);
        //        penDefault.setBrush(brushDefault);
        penDefault.setWidthF(0.5);

        m_tracer = new QCPItemTracer(m_plot);
        m_tracer->setStyle(QCPItemTracer::tsCircle);
        m_tracer->setPen(penDefault);
        m_tracer->setBrush(brushDefault);

        if(m_type != MouseMarker)
        {
            m_label = new QCPItemText(m_plot);
            m_label->setLayer("overlay");
            m_label->setClipToAxisRect(false);
            m_label->setPadding(QMargins(5, 5, 5, 5));
            m_label->setBrush(brushDefault);
            m_label->setPen(penDefault);
            m_label->position->setParentAnchor(m_tracer->position);
    //        m_label->setFont(QFont("����", 8));
            m_label->setFont(QFont("Arial", 8));
            m_label->setColor(clrDefault);
            m_label->setText("");
        }

        m_arrow = new QCPItemLine(m_plot);
        m_arrow->setPen(penDefault);
        m_arrow->setLayer("overlay");
        m_arrow->setClipToAxisRect(false);
        m_arrow->setHead(QCPLineEnding::esSpikeArrow);//����ͷ��Ϊ��ͷ��״

        switch (m_type)
        {
        case XAxisTracer:
        {
            m_tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
            m_tracer->position->setTypeY(QCPItemPosition::ptAxisRectRatio);
            m_tracer->setSize(7);
            m_label->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);

            m_arrow->end->setParentAnchor(m_tracer->position);
            m_arrow->start->setParentAnchor(m_arrow->end);
            m_arrow->start->setCoords(0, 20);//ƫ����
            break;
        }
        case MouseMarker:
        {
            m_marker = new QCPItemTextEx(m_plot);
            m_marker->setLayer("overlay");
            m_marker->setClipToAxisRect(false);
            m_marker->setPadding(QMargins(5, 5, 5, 5));
            m_marker->setBrush(brushDefault);
            m_marker->setPen(penDefault);
            m_marker->position->setParentAnchor(m_tracer->position);
    //        m_label->setFont(QFont("����", 8));
            m_marker->setFont(QFont("Arial", 8));
            m_marker->setColor(clrDefault);
            m_marker->setText("");

            m_tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
            m_tracer->position->setTypeY(QCPItemPosition::ptAxisRectRatio);
            m_tracer->setSize(7);
            m_marker->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);

            m_arrow->end->setParentAnchor(m_tracer->position);
            m_arrow->start->setParentAnchor(m_arrow->end);
            m_arrow->start->setCoords(0, 20);//ƫ����
            m_marker_id = -1;
            break;
        }
        case YAxisTracer:
        {
            m_tracer->position->setTypeX(QCPItemPosition::ptAxisRectRatio);
            m_tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
            m_tracer->setSize(7);
            m_label->setPositionAlignment(Qt::AlignRight | Qt::AlignHCenter);

            m_arrow->end->setParentAnchor(m_tracer->position);
            m_arrow->start->setParentAnchor(m_label->position);
            m_arrow->start->setCoords(-20, 0);//ƫ����
            break;
        }
        case DataTracer:
        {
            m_tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
            m_tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
            m_tracer->setSize(5);

            m_label->setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);

            m_arrow->end->setParentAnchor(m_tracer->position);
            m_arrow->start->setParentAnchor(m_arrow->end);
            m_arrow->start->setCoords(20, 0);
            break;
        }
        default:
            break;
        }
        setVisible(false);
    }
}

MouseTracer::~MouseTracer()
{
    if(m_plot)
    {
        if (m_tracer)
            m_plot->removeItem(m_tracer);
        if (m_label)
            m_plot->removeItem(m_label);
        if (m_marker)
            m_plot->removeItem(m_marker);
        if (m_arrow)
            m_plot->removeItem(m_arrow);
    }
}

void MouseTracer::setPen(const QPen &pen)
{
    if(m_tracer)
        m_tracer->setPen(pen);
    if(m_arrow)
        m_arrow->setPen(pen);
}

void MouseTracer::setBrush(const QBrush &brush)
{
    if(m_tracer)
        m_tracer->setBrush(brush);
}

void MouseTracer::setText(const QString &text)
{
    if(m_label)
        m_label->setText(text);
    if(m_marker)
        m_marker->setText(text);
}

void MouseTracer::setLabelPen(const QPen &pen)
{
    if(m_label)
    {
        m_label->setPen(pen);
        m_label->setBrush(Qt::NoBrush);
        m_label->setColor(pen.color());
    }
}

void MouseTracer::updatePosition(double xValue, double yValue)
{
    if (!m_visible)
    {
        setVisible(true);
        m_visible = true;
    }

    if (yValue > m_plot->yAxis->range().upper)
        yValue = m_plot->yAxis->range().upper;

    switch (m_type)
    {
    case XAxisTracer:
    {
        m_tracer->position->setCoords(xValue, 1);
        m_label->position->setCoords(0, 15);
        m_arrow->start->setCoords(0, 15);
        m_arrow->end->setCoords(0, 0);
        setText(QString::number(xValue));
        break;
    }
    case YAxisTracer:
    {
        m_tracer->position->setCoords(0, yValue);
        m_label->position->setCoords(-20, 0);
//        m_arrow->start->setCoords(20, 0);
//        m_arrow->end->setCoords(0, 0);
        setText(QString::number(yValue));
        break;
    }
    case DataTracer:
    {
        m_tracer->position->setCoords(xValue,yValue);
        m_label->position->setCoords(20, 0);
        setText(QString("x:%1,y:%2").arg(xValue).arg(yValue));
        break;
    }
    case MouseMarker:
    {
        m_tracer->position->setCoords(m_x_value, 1);
        m_marker->position->setCoords(0, 15);
        m_arrow->start->setCoords(0, 15);
        m_arrow->end->setCoords(0, 0);
        setText(QString("%1").arg(m_marker_id));
        break;
    }
    default:
        break;
    }
}

void MouseTracer::setVisible(bool m_visible)
{
    m_visible = m_visible;
    if(m_tracer)
        m_tracer->setVisible(m_visible);
    if(m_label)
        m_label->setVisible(m_visible);
    if(m_marker)
        m_marker->setVisible(m_visible);
    if(m_arrow)
        m_arrow->setVisible(m_visible);
}

void MouseTracer::removeMarker()
{
    this->m_plot->removeItem(m_marker);
    this->m_plot->removeItem(m_tracer);
    this->m_plot->removeItem(m_arrow);
}

MouseTraceLine::MouseTraceLine(QCustomPlot *_plot, MouseTraceLine::LineType _type, QObject *parent)
    : QObject(parent),
    m_type(_type),
    m_plot(_plot)
{
    m_lineV = Q_NULLPTR;
    m_lineH = Q_NULLPTR;
    initLine();
}

MouseTraceLine::~MouseTraceLine()
{
    if(m_plot)
    {
        if (m_lineV)
            m_plot->removeItem(m_lineV);
        if (m_lineH)
            m_plot->removeItem(m_lineH);
    }
}

void MouseTraceLine::initLine()
{
    if(m_plot)
    {
        QPen linesPen(Qt::red, 1, Qt::DashLine);
        if(VerticalLine == m_type || Both == m_type)
        {
            m_lineV = new QCPItemStraightLine(m_plot);//��ֱ��
            m_lineV->setLayer("overlay");
            m_lineV->setPen(linesPen);
            m_lineV->setClipToAxisRect(true);
            m_lineV->point1->setCoords(0, 0);
            m_lineV->point2->setCoords(0, 0);
        }

        if(HorizonLine == m_type || Both == m_type)
        {
            m_lineH = new QCPItemStraightLine(m_plot);//ˮƽ��
            m_lineH->setLayer("overlay");
            m_lineH->setPen(linesPen);
            m_lineH->setClipToAxisRect(true);
            m_lineH->point1->setCoords(0, 0);
            m_lineH->point2->setCoords(0, 0);
        }
    }
}

void MouseTraceLine::updatePosition(double xValue, double yValue)
{
    if(VerticalLine == m_type || Both == m_type)
    {
        if(m_lineV)
        {
            m_lineV->point1->setCoords(xValue, m_plot->yAxis->range().lower);
            m_lineV->point2->setCoords(xValue, m_plot->yAxis->range().upper);
        }
    }

    if(HorizonLine == m_type || Both == m_type)
    {
        if(m_lineH)
        {
            m_lineH->point1->setCoords(m_plot->xAxis->range().lower, yValue);
            m_lineH->point2->setCoords(m_plot->xAxis->range().upper, yValue);
        }
    }
}

QCPItemTextEx::QCPItemTextEx(QCustomPlot *parentPlot):QCPItemText(parentPlot)
{
    m_plot = parentPlot;
}

QCPItemTextEx::~QCPItemTextEx()
{

}

void QCPItemTextEx::draw(QCPPainter *painter)
{
    QPointF pos(position->pixelPosition());
    QTransform transform = painter->transform();
    transform.translate(pos.x(), pos.y());
    if (!qFuzzyIsNull(mRotation))
      transform.rotate(mRotation);
    painter->setFont(mainFont());
    QRect textRect = painter->fontMetrics().boundingRect(0, 0, 0, 0, Qt::TextDontClip|mTextAlignment, mText);
    QRect textBoxRect = textRect.adjusted(-mPadding.left(), -mPadding.top(), mPadding.right(), mPadding.bottom());
    QPointF textPos = getTextDrawPoint(QPointF(0, 0), textBoxRect, mPositionAlignment); // 0, 0 because the transform does the translation
    textRect.moveTopLeft(textPos.toPoint()+QPoint(mPadding.left(), mPadding.top()));
    textBoxRect.moveTopLeft(textPos.toPoint());
    int clipPad = qCeil(mainPen().widthF());
    QRect boundingRect = textBoxRect.adjusted(-clipPad, -clipPad, clipPad, clipPad);
    if (transform.mapRect(boundingRect).intersects(painter->transform().mapRect(clipRect())))
    {
      painter->setTransform(transform);
      if ((mainBrush().style() != Qt::NoBrush && mainBrush().color().alpha() != 0) ||
          (mainPen().style() != Qt::NoPen && mainPen().color().alpha() != 0))
      {
        painter->setPen(mainPen());
        painter->setBrush(mainBrush());
        QPointF pt1(textBoxRect.left()+textBoxRect.width()/2,textBoxRect.top());
        QPointF pt2(textBoxRect.left(),textBoxRect.bottom());
        QPointF pt3(textBoxRect.right(),textBoxRect.bottom());
        painter->drawLine(pt1,pt2);
        painter->drawLine(pt2,pt3);
        painter->drawLine(pt3,pt1);
//        painter->drawRect(textBoxRect);
      }
      painter->setBrush(Qt::NoBrush);
      painter->setPen(QPen(mainColor()));
      painter->drawText(textRect, Qt::TextDontClip|mTextAlignment, mText);
    }
}
