#ifndef TESTDRAWWGT_H
#define TESTDRAWWGT_H

#include <QWidget>

class TestDrawWgt : public QWidget
{
    Q_OBJECT
public:
    explicit TestDrawWgt(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // TESTDRAWWGT_H
