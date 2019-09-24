#ifndef CHILDWIDGETF_H
#define CHILDWIDGETF_H

#include <QWidget>

namespace Ui {
class ChildWidgetF;
}

class ChildWidgetF : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetF(QWidget *parent = 0);
    ~ChildWidgetF();
signals:
    void sendWriteSocket(QString);
protected:
    void showEvent(QShowEvent *event);

private:
    void updateDisplay();
    QVector<QVector<QString>> queryAll(QString tablename);

private slots:
    void onHeaderClicked(int,int);
private slots:
    void on_btn_find_clicked();

    void on_btn_look_clicked();
 void acceptSocketData(QString);
private:
    Ui::ChildWidgetF *ui;
    int selectrow;
    QStringList datalist;
};

#endif // CHILDWIDGETF_H
