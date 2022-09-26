#include "welcomewidget.h"
#include <QIcon>
#include "TitleBar.h"
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QCheckBox>
#include <QSqlQuery>
WelcomeWidget::WelcomeWidget()
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags() | Qt::Widget);
    setWindowIcon(QIcon(":/icon/24x24.png"));
    resize(1000,700);
    TitleBar *pTitleBar = new TitleBar(this);
    pTitleBar->setTitle(u8"     登录");
    pTitleBar->setFixedWidth(1000);
    installEventFilter(pTitleBar);
    TitleHeight = pTitleBar->height();

    QVBoxLayout* vAll = new QVBoxLayout();
    QHBoxLayout* hBox1 = new QHBoxLayout();
    QHBoxLayout* hBox2 = new QHBoxLayout();
    QHBoxLayout* hBox3 = new QHBoxLayout();
    QHBoxLayout* hBox4 = new QHBoxLayout();

    QLabel* userNameLabel = new QLabel(u8"用户名:");
    userNameLabel->setStyleSheet("QLabel{color:rgba(255,255,255,150);border:1px;\
                            border-radius:8px;\
                            background-color:rgba(24,33,38,0);font-family:\"LiSu\";\
                            font-size: 30px;font-weight:bold;}");
    userNameLineEdit = new QLineEdit();
    userNameLineEdit->setStyleSheet("QLineEdit{color:rgba(255,255,255,200);border:1px solid rgba(255,255,255,100);\
                            border-radius:8px;\
                            background-color:rgba(24,33,38,0);font-family:\"LiSu\";\
                            font-size: 30px;font-weight:bold;\
                            max-width:300px;}");
    userNameLineEdit->setAlignment(Qt::AlignCenter);
    userNameLineEdit->setText(u8"username");
    hBox1->addStretch(1);
//    hBox1->addWidget(userNameLabel);
    hBox1->addWidget(userNameLineEdit);
    hBox1->addStretch(1);

    QLabel* passwordLabel = new QLabel(u8" 密码: ");
    passwordLabel->setStyleSheet("QLabel{color:rgba(255,255,255,255);border:1px;\
                            border-radius:8px;\
                            background-color:rgba(24,33,38,0);font-family:\"LiSu\";\
                            font-size: 30px;font-weight:bold;}");
    passwordLineEdit = new QLineEdit();
    connect(passwordLineEdit,SIGNAL(textEdited(const QString&)),this,SLOT(slot_password_editEdited(const QString&)));
    passwordLineEdit->setStyleSheet("QLineEdit{color:rgba(255,255,255,200);border:1px solid rgba(255,255,255,100);\
                            border-radius:8px;\
                            background-color:rgba(24,33,38,0);font-family:\"LiSu\";\
                            font-size: 30px;font-weight:bold;\
                            max-width:300px;}");
    passwordLineEdit->setAlignment(Qt::AlignCenter);
    passwordLineEdit->setText(u8"password");
    hBox2->addStretch(1);
//    hBox2->addWidget(passwordLabel);
    hBox2->addWidget(passwordLineEdit);
    hBox2->addStretch(1);

    QCheckBox* ngCheckBox = new QCheckBox(u8"Remember me");
//    ngCheckBox->setStyleSheet("QCheckBox::indicator{background-color:rgba(255,255,255,255);}");
    hBox3->addStretch(1);
    hBox3->addWidget(ngCheckBox);
    hBox3->addStretch(1);

    QPushButton* btnOK = new QPushButton(u8"     Login     ");
    connect(btnOK,SIGNAL(clicked()),this,SLOT(slot_user_login()));
    btnOK->setStyleSheet("QPushButton{background-color:rgba(24,33,38,0);\
                            min-width:300px;max-width:300px;font-family:'LiSu';}");
    QPushButton* btnCancel = new QPushButton(u8"   取 消   ");
    btnCancel->setStyleSheet("QPushButton{background-color:rgba(24,33,38,0);}");
    hBox4->addStretch(1);
    hBox4->addWidget(btnOK);
//    hBox4->addStretch(1);
//    hBox4->addWidget(btnCancel);
    hBox4->addStretch(1);

    vAll->addStretch(9);
    vAll->addLayout(hBox1);
    vAll->addLayout(hBox2);
    vAll->addLayout(hBox3);
    vAll->addLayout(hBox4);
    vAll->addStretch(4);
    this->setLayout(vAll);
}

void WelcomeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPixmap *img = new QPixmap(":/icon/back_net1.jpg");
    QRect backR(0,0,this->width(),this->height());
    QRect imgRect;
    imgRect.setTopLeft(QPoint(1,1));
    imgRect.setBottomRight(QPoint(this->width()-2,this->height()-1));
    painter.drawPixmap(backR,*img);

    //绘图
    int rAllLeft,rAllTop,rAllWidth,rAllHeight;
    rAllWidth = this->rect().width()*3/5;
    rAllHeight = this->height()*4/6;
    rAllLeft = this->rect().width()/5;
    rAllTop = TitleHeight*8;
    QRect rAll(rAllLeft,rAllTop,rAllWidth,this->height()*2.3/6);
    QRect rHead(rAllLeft,rAllTop,rAllWidth,rAllHeight/6);
    painter.save();
    painter.setPen(QColor(161,158,203,100));
    painter.setBrush(QBrush(QColor(161,158,203,100)));
    painter.drawRoundRect(rAll,10,20);
    painter.restore();

    painter.save();
    QPixmap *imgHead = new QPixmap(":/icon/girl.png");
    QRect eRect(this->rect().width()/2-rHead.height(),TitleHeight*3,rHead.height()*2,rHead.height()*2);
    QBrush br(*imgHead);
    painter.setPen(QColor(0,0,0,0));
    painter.setBrush(br);
    painter.setBrushOrigin(this->rect().width()/2-rHead.height(),TitleHeight*3);//设置画刷规则，不设置，画刷默认为平铺绘制
    painter.drawEllipse(eRect);
    painter.restore();

    int x1,y1,x2,y2;
    x1 = rAllLeft + 10;//左上
    y1 = rAllTop + 10;

    //右上
    x2 = rAllLeft + rAllWidth - 40;
    y2 = rAllTop + 10;

    QPainterPath path[2];
    path[0].addEllipse(QRectF(x1,y1,25,25));
    path[1].addEllipse(QRectF(x2,y2,25,25));

//    for (int i=0;i<2;i++)
//    {
//        painter.fillPath(path[i],QColor(0,0,0));
//    }
}

void WelcomeWidget::slot_password_editEdited(const QString &strText)
{
    passwordLineEdit->setEchoMode(QLineEdit::Password);
}

void WelcomeWidget::slot_user_login()
{
//    QString strSql = QString("select * from public.%1").arg(constUserInfoTable);
//    QSqlQuery queryResult;
//    bool loginSign = false;
//    if(GDataFactory::get_pgsql()->GetQueryResult(strSql,queryResult))
//    {
//        QLOG_TRACE()<<u8"query database success!";
//        QString uName = this->userNameLineEdit->text();
//        QString uPassword = this->passwordLineEdit->text();
//        while(queryResult.next())
//        {
//            if((uName == queryResult.value(1).toString())&&(uPassword == queryResult.value(2).toString()))
//            {
//                loginSign = true;
//                break;
//            }
//            else
//                continue;
//        }
//    }

//    if(loginSign == true)
//    {
//        QString tmpLog = this->userNameLineEdit->text() + " login success!";
//        QLOG_TRACE()<<tmpLog;
//        this->accept();
//    }
//    else
//        ;
}
