#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TitleBar.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "centralwgt.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags()| Qt::Widget);
    setWindowIcon(QIcon(":/icon/24x24.png"));
    resize(1200,1000);
//    resize(600,500);

    CentralWgt* cWgt = new CentralWgt(this);
    cWgt->setGeometry(0,40,this->width(),this->height()-40);
    cWgt->show();

    TitleBar *pTitleBar = new TitleBar(this);
    pTitleBar->setTitle(u8"Qt自开发控件集锦");
    pTitleBar->setFixedWidth(1200);
    installEventFilter(pTitleBar);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(QColor(255,255,255,100),2));
    painter.drawRect(this->rect());
}
