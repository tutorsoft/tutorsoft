#ifndef CHILDWIDGETE_H
#define CHILDWIDGETE_H

#include <QWidget>

namespace Ui {
class ChildWidgetE;
}

class ChildWidgetE : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetE(QWidget *parent = 0);
    ~ChildWidgetE();
signals:
    void sendWriteSocket(QString);
protected:
    void showEvent(QShowEvent *event);

private:
    void updateDisplay();
    QVector<QVector<QString>> queryAll(QString tablename);

private slots:
    void onHeaderClicked(int,int);

 void acceptSocketData(QString);
private slots:
    void on_btn_find_clicked();

    void on_btn_look_clicked();

private:
     int selectrow;
    Ui::ChildWidgetE *ui;
};

#endif // CHILDWIDGETE_H
