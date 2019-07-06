#ifndef CHILDWIDGETH_H
#define CHILDWIDGETH_H

#include <QWidget>

namespace Ui {
class ChildWidgetH;
}

class ChildWidgetH : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetH(QWidget *parent = 0);
    ~ChildWidgetH();
signals:
    void sendWriteSocket(QString);
protected:
    void showEvent(QShowEvent *event);

private slots:
    void onHeaderClicked(int,int);

    void on_btn_look_clicked();
 void acceptSocketData(QString);
private:
    Ui::ChildWidgetH *ui;
        int selectrow;
};

#endif // CHILDWIDGETH_H
