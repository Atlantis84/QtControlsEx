#include "qcustomplotex.h"
#include <QMenu>
#include <QSignalMapper>
QCustomPlotEx::QCustomPlotEx(QWidget *parent):QCustomPlot(parent)
  ,m_isShowTracer(false)
  ,m_xTracer(Q_NULLPTR)
  ,m_yTracer(Q_NULLPTR)
  ,m_dataTracers(QList<MouseTracer *>())
  ,m_lineTracer(Q_NULLPTR)
{
}

void QCustomPlotEx::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);

    if(m_isShowTracer)
    {
//        for(int i=0;i<m_xMarkerList.length();i++)
//            m_xMarkerList[i]->updatePosition(0.0,0.0);
        //当前鼠标位置（像素坐标）
        int x_pos = event->pos().x();
        int y_pos = event->pos().y();

        //像素坐标转成实际的x,y轴的坐标
        float x_val = this->xAxis->pixelToCoord(x_pos);
        float y_val = this->yAxis->pixelToCoord(y_pos);

        if(Q_NULLPTR == m_xTracer)
            m_xTracer = new MouseTracer(this, MouseTracer::XAxisTracer);//x轴
        m_xTracer->updatePosition(x_val, y_val);
        m_xTracer->setVisible(true);

        if(Q_NULLPTR == m_yTracer)
            m_yTracer = new MouseTracer(this, MouseTracer::YAxisTracer);//y轴
        m_yTracer->updatePosition(x_val, y_val);
        m_yTracer->setVisible(true);

        int nTracerCount = m_dataTracers.count();
        int nGraphCount = graphCount();
        if(nTracerCount < nGraphCount)
        {
            qDebug()<<nTracerCount;
            for(int i = nTracerCount; i < nGraphCount; ++i)
            {
                MouseTracer *tracer = new MouseTracer(this, MouseTracer::DataTracer);
                m_dataTracers.append(tracer);
            }
        }
        else if(nTracerCount > nGraphCount)
        {
            for(int i = nGraphCount; i < nTracerCount; ++i)
            {
                MouseTracer *tracer = m_dataTracers[i];
                if(tracer)
                {
                    tracer->setVisible(false);
                }
            }
        }
        for (int i = 0; i < nGraphCount; ++i)
        {
            MouseTracer *tracer = m_dataTracers[i];
            if(!tracer)
                tracer = new MouseTracer(this, MouseTracer::DataTracer);
            tracer->setVisible(true);
            tracer->setPen(this->graph(i)->pen());
            tracer->setBrush(Qt::NoBrush);
            tracer->setLabelPen(this->graph(i)->pen());
            auto iter = this->graph(i)->data()->findBegin(x_val);
            double value = iter->mainValue();
            tracer->updatePosition(x_val, value);
        }

        if(Q_NULLPTR == m_lineTracer)
            m_lineTracer = new MouseTraceLine(this,MouseTraceLine::Both);//直线
        m_lineTracer->updatePosition(x_val, y_val);

        this->replot();//曲线重绘
    }
}

void QCustomPlotEx::mouseWheel(QWheelEvent *event)
{
//    if(Q_NULLPTR != m_xMarker)
//        m_xMarker->updatePosition(marker_xval,marker_yval);
//    this->replot();
    QCustomPlot::mouseWheel(event);
}

int id=0;
void QCustomPlotEx::mousePressEvent(QMouseEvent *event)
{
    QCustomPlot::mousePressEvent(event);
    if(event->modifiers() == Qt::SHIFT)
    {
        if(event->button() == Qt::RightButton)
        {
            QMenu * menu=new QMenu;
            lstAction.clear();
            QAction * saveaction=new QAction;
            lstAction.push_back(saveaction);
            saveaction->setText(u8"菜单扩展");
            menu->addAction(saveaction);

            for(int i=0;i<m_xMarkerList.length();i++)
            {
                int mID = m_xMarkerList[i]->getMarkerID();
                QAction * action=new QAction;
                QString ss = QString(u8"删除Marker%1").arg(mID);
                action->setText(ss);
                lstAction.push_back(action);
                menu->addAction(action);
            }

            QSignalMapper* mapper = new QSignalMapper();
            for (int i=0;i<lstAction.length();i++)
            {
                mapper->setMapping(lstAction[i],i);
                connect(lstAction[i],SIGNAL(triggered()),mapper,SLOT(map()));
            }
            connect(mapper,SIGNAL(mapped(int)),this,SLOT(slot_menu_click(int)));

            menu->exec(QCursor::pos());
        }
        else if(event->button() == Qt::LeftButton)
        {
            id++;
            if((id != 0) && (id <5))
            {
                QCPItemText* m_testText = new QCPItemText(this);
                m_testText->setPositionAlignment(Qt::AlignLeft);
                m_testText->position->setType(QCPItemPosition::ptAxisRectRatio);
                m_testText->position->setCoords(0.07*(id-1),0.0);
                m_testText->setPen(QPen(QColor(255,0,0,0)));
                m_testText->setColor(QColor(255,0,0));
                m_testText->setFont(QFont("FangSong", 10));
                if(id == 1)
                    m_testText->setText(u8"实时值:");
                else if(id == 2)
                    m_testText->setText(u8"最大值:");
                else if(id == 3)
                    m_testText->setText(u8"最小值:");
                else if(id == 4)
                    m_testText->setText(u8"平均值:");
            }
        }
    }
    else
    {
        if(event->button() == Qt::RightButton)
        {
            if(m_xMarkerList.length()<5)
            {
                int x_pos = event->pos().x();
                int y_pos = event->pos().y();

                //像素坐标转成实际的x,y轴的坐标
                float marker_xval = this->xAxis->pixelToCoord(x_pos);
                float marker_yval = this->yAxis->pixelToCoord(y_pos);

                MouseTracer* marker = new MouseTracer(this,MouseTracer::MouseMarker);
                marker->setVisible(true);
                marker->setMarkerID(m_xMarkerList.length()+1);
                marker->setXValue(marker_xval);

                QCPItemText* m_testT = new QCPItemText(this);
                m_testT->setPositionAlignment(Qt::AlignLeft);
                m_testT->position->setType(QCPItemPosition::ptAxisRectRatio);
                m_testT->position->setCoords(0.75,m_xMarkerList.length()*0.08);
                m_testT->setPen(QPen(QColor(255,0,0,0)));
                m_testT->setColor(QColor(255,0,0));
                m_testT->setFont(QFont("FangSong", 10));
                int mID = m_xMarkerList.length()+1;
                QString tmpText = QString("Marker%1:x %2 y %3").arg(mID).arg(marker_xval).arg(marker_yval);
                m_testT->setText(tmpText);
                lstText.push_back(m_testT);

                m_xMarkerList.push_back(marker);

            }

            for(int i=0;i<m_xMarkerList.length();i++)
                m_xMarkerList[i]->updatePosition(0.0,0.0);
            this->replot();
        }
    }
}

void QCustomPlotEx::slot_menu_click(int id)
{
    if(lstAction.length()>=2)
    {
        QCPItemText* itemToRemove;
        bool bFound = false;
        int rID = -1;
        for(int i=id;i<id+1;i++)
        {
            QString tmpAction = lstAction[i]->text().at(lstAction[i]->text().length() -1);
            if(tmpAction.toInt() == m_xMarkerList[i-1]->getMarkerID())
            {
                for(int j=0;j<lstText.length();j++)
                {
                    if(lstText[j]->text().contains(lstAction[i]->text().mid(2,7)))
                    {
                        qDebug()<<"lstText[j]->text():"<<lstText[j]->text();
                        qDebug()<<"lstAction[i]->text().mid(2,6):"<<lstAction[i]->text().mid(2,7);
                        itemToRemove = lstText[j];
                        bFound = true;
                        rID = i;
                    }
                }
            }
            else
                continue;
        }

        if(bFound)
        {
            this->removeItem(itemToRemove);
            this->m_xMarkerList[rID-1]->removeMarker();
            this->m_xMarkerList.removeAt(rID-1);
            this->lstText.removeOne(itemToRemove);
            this->replot();
        }
    }
}

void QCustomPlotEx::showSS(bool show)
{
    m_isShowTracer = show;
    if(m_xTracer)
        m_xTracer->setVisible(m_isShowTracer);
//    foreach (MouseTracer *tracer, m_dataTracers)
//    {
//        if(tracer)
//            tracer->setVisible(m_isShowTracer);
//    }
//    if(m_lineTracer)
//        m_lineTracer->setVisible(m_isShowTracer);
}
