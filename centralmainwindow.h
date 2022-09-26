#ifndef CENTRALMAINWINDOW_H
#define CENTRALMAINWINDOW_H

#include <QMainWindow>

class CentralMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CentralMainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // CENTRALMAINWINDOW_H
