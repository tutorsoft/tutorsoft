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

private:
    Ui::ChildWidgetF *ui;
    int selectrow;
};

#endif // CHILDWIDGETF_H
