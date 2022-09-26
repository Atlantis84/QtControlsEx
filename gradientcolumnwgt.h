#ifndef GRADIENTCOLUMNWGT_H
#define GRADIENTCOLUMNWGT_H

#include <QWidget>

class GradientColumnWgt : public QWidget
{
    Q_OBJECT
public:
    static GradientColumnWgt* get_instance()
    {
        if(m_pGradientColumnWgt == nullptr)
            m_pGradientColumnWgt = new GradientColumnWgt();
        return m_pGradientColumnWgt;
    }
private:
    explicit GradientColumnWgt(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

    static GradientColumnWgt* m_pGradientColumnWgt;

signals:

public slots:
};

#endif // GRADIENTCOLUMNWGT_H
