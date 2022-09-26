#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QDialog>
class QLineEdit;
class WelcomeWidget : public QDialog
{
    Q_OBJECT
public:
    explicit WelcomeWidget();

private:
    void paintEvent(QPaintEvent *event);
    int TitleHeight;
    QLineEdit* passwordLineEdit;
    QLineEdit* userNameLineEdit;
public:

signals:

public slots:
    void slot_password_editEdited(const QString& strText);
    void slot_user_login();
};

#endif // WELCOMEWIDGET_H
