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
protected:
    void showEvent(QShowEvent *event);

private:
    void updateDisplay();
    QVector<QVector<QString>> queryAll(QString tablename);

private slots:
    void onHeaderClicked(int,int);
private slots:
    void on_btn_add_clicked();

    void on_btn_del_clicked();

private:
    Ui::ChildWidgetB *ui;
    int selectrow;
};

#endif // CHILDWIDGETB_H
