#ifndef CHILDWIDGETB_H
#define CHILDWIDGETB_H

#include <QWidget>

namespace Ui {
class ChildWidgetB;
}

class ChildWidgetB : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetB(QWidget *parent = 0);
    ~ChildWidgetB();

private slots:
    void on_btn_resiger_clicked();

private:
    Ui::ChildWidgetB *ui;
};

#endif // CHILDWIDGETB_H
