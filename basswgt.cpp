#include "basswgt.h"
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "bassdywgt.h"
#include "bassstwgt.h"

BassWgt::BassWgt(QWidget *parent) : QWidget(parent)
{
    if (!BASS_Init(-1,44100,0,(HWND)this->winId(),NULL))
        qDebug()<<u8"初始化设备失败!";

    if (HIWORD(BASS_GetVersion())!=BASSVERSION)
        qDebug()<<u8"Bass.dll版本不合适!";

    QVBoxLayout* vAll = new QVBoxLayout();
    QHBoxLayout* hBox = new QHBoxLayout();
    QHBoxLayout* hBox1 = new QHBoxLayout();
    BassDyWgt* bassDyWgt = new BassDyWgt();
    BassStWgt* bassStWgt = new BassStWgt();
    hBox->addWidget(bassStWgt);
    hBox1->addWidget(bassDyWgt);
    vAll->addLayout(hBox);
    vAll->addLayout(hBox1);
    this->setLayout(vAll);
}

void BassWgt::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
//    painter.fillRect(this->rect(),QBrush(QColor(255,255,0,100)));

}
