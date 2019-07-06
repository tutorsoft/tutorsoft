#ifndef CHILDWIDGETJ_H
#define CHILDWIDGETJ_H

#include <QWidget>

namespace Ui {
class ChildWidgetJ;
}

class ChildWidgetJ : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetJ(QWidget *parent = 0);
    ~ChildWidgetJ();
signals:
    void sendWriteSocket(QString);
protected:
    void showEvent(QShowEvent *event);

private slots:
    void onHeaderClicked(int,int);

    void on_btn_look_clicked();
 void acceptSocketData(QString);
private:
    Ui::ChildWidgetJ *ui;
        int selectrow;
};

#endif // CHILDWIDGETJ_H
