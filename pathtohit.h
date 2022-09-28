#ifndef PATHTOHIT_H
#define PATHTOHIT_H

#include <QObject>
#include <QWidget>
#include <QPainterPath>
class PathToHit : public QWidget
{
    Q_OBJECT
public:
    explicit PathToHit(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QPainterPath* pathToPaint;
signals:

public slots:
};

#endif // PATHTOHIT_H
