#ifndef REGISTERTEACHERWIDGET_H
#define REGISTERTEACHERWIDGET_H

#include <QDialog>

namespace Ui {
class RegisterTeacherWidget;
}

class RegisterTeacherWidget : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterTeacherWidget(QWidget *parent = 0);
    ~RegisterTeacherWidget();
signals:
    void sendWriteSocket(QString);
private slots:
    void on_btn_resiger_clicked();

    void on_btn_quit_clicked();
 void acceptSocketData(QString);
private:
    Ui::RegisterTeacherWidget *ui;
};

#endif // REGISTERTEACHERWIDGET_H
