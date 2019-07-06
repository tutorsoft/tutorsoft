#ifndef REGISTERSTUDENTWIDGET_H
#define REGISTERSTUDENTWIDGET_H

#include <QDialog>

namespace Ui {
class RegisterStudentWidget;
}

class RegisterStudentWidget : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterStudentWidget(QWidget *parent = 0);
    ~RegisterStudentWidget();

private slots:
    void on_btn_resiger_clicked();

    void on_btn_quit_clicked();

private:
    Ui::RegisterStudentWidget *ui;
};

#endif // REGISTERSTUDENTWIDGET_H
