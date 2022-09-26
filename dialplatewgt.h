#ifndef DIALPLATEWGT_H
#define DIALPLATEWGT_H

#include <QObject>
#include <QWidget>

class DialPlateWgt : public QWidget
{
    Q_OBJECT
public:
    explicit DialPlateWgt(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent *event);
    QPoint ptCenter;
    int delayValue;

signals:

public slots:
};

#endif // DIALPLATEWGT_H
