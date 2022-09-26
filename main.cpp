#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "testdrawwgt.h"
#include "dialplatewgt.h"
#include "gradientcolumnwgt.h"
#include "welcomewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString qssFile = ":/icon/darkgray.qss";
    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
//    MainWindow w;
//    TestDrawWgt w;
//    DialPlateWgt w;
//    WelcomeWidget w;
//    w.show();
    GradientColumnWgt::get_instance()->show();

    return a.exec();
}
