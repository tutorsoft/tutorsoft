#ifndef CHILDWIDGETC_H
#define CHILDWIDGETC_H

#include <QWidget>

namespace Ui {
class ChildWidgetC;
}

class ChildWidgetC : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetC(QWidget *parent = 0);
    ~ChildWidgetC();
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
    Ui::ChildWidgetC *ui;
    int selectrow;
};

#endif // CHILDWIDGETC_H
