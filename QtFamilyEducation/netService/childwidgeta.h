#ifndef CHILDWIDGETA_H
#define CHILDWIDGETA_H

#include <QWidget>

namespace Ui {
class ChildWidgetA;
}

class ChildWidgetA : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetA(QWidget *parent = 0);
    ~ChildWidgetA();


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
    Ui::ChildWidgetA *ui;
    int selectrow;
};

#endif // CHILDWIDGETA_H
