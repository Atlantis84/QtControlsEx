#include "centralmainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QTextEdit>
CentralMainWindow::CentralMainWindow(QWidget *parent) : QMainWindow(parent)
{
    QVBoxLayout* vAll = new QVBoxLayout();
    QTextEdit* textEdit = new QTextEdit();
    vAll->addWidget(textEdit);
    this->setLayout(vAll);
}

void CentralMainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(this->rect(),QBrush(QColor(255,0,0,100)));

}
