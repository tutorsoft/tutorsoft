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
signals:
    void sendWriteSocket(QString);
private slots:
    void on_btn_resiger_clicked();
 void acceptSocketData(QString);
private:
    Ui::ChildWidgetB *ui;
};

#endif // CHILDWIDGETB_H
