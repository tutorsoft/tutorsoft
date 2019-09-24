#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include <QWidget>
#include "form/childwidgeta.h"
#include "form/childwidgetb.h"
#include "form/childwidgetc.h"
#include "form/childwidgetd.h"
#include "form/childwidgete.h"
#include "form/childwidgetf.h"

namespace Ui {
class StudentWidget;
}


class StudentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentWidget(QWidget *parent = 0);
    ~StudentWidget();

private slots:
    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_6_clicked();

    void on_btn_quit_clicked();

signals:
    void sendQuit();
private:
    Ui::StudentWidget *ui;
    ChildWidgetA *m_ChildWidgetA;
    ChildWidgetB *m_ChildWidgetB;
    ChildWidgetC *m_ChildWidgetC;
    ChildWidgetD *m_ChildWidgetD;
    ChildWidgetE *m_ChildWidgetE;
    ChildWidgetF *m_ChildWidgetF;
};

#endif // STUDENTWIDGET_H
