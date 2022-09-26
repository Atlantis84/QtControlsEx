#ifndef BASSWGT_H
#define BASSWGT_H

#include <QWidget>

class BassWgt : public QWidget
{
    Q_OBJECT
public:
    explicit BassWgt(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // BASSWGT_H
