#ifndef CHILDWIDGETD_H
#define CHILDWIDGETD_H

#include <QWidget>

namespace Ui {
class ChildWidgetD;
}

class ChildWidgetD : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetD(QWidget *parent = 0);
    ~ChildWidgetD();
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
    Ui::ChildWidgetD *ui;
    int selectrow;
};

#endif // CHILDWIDGETD_H
