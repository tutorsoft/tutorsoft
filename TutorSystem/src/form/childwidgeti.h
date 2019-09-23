#ifndef CHILDWIDGETI_H
#define CHILDWIDGETI_H

#include <QWidget>

namespace Ui {
class ChildWidgetI;
}

class ChildWidgetI : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetI(QWidget *parent = 0);
    ~ChildWidgetI();
signals:
    void sendWriteSocket(QString);
protected:
    void showEvent(QShowEvent *event);

private slots:
    void onHeaderClicked(int,int);

    void on_btn_look_clicked();
 void acceptSocketData(QString);
private:
    Ui::ChildWidgetI *ui;
        int selectrow;
};

#endif // CHILDWIDGETI_H
