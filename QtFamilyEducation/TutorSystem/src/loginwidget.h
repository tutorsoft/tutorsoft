#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "registerteacherwidget.h"
#include "registerstudentwidget.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

signals:
    void sendLoginSignal(bool);
    void sendWriteSocket(QString);

private slots:
    void on_btn_login_clicked();

    void on_btn_register_clicked();

    void acceptSocketData(QString);
private:
    Ui::LoginWidget *ui;

};

#endif // LOGINWIDGET_H
