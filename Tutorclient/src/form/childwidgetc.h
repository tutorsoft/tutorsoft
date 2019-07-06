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
signals:
    void sendWriteSocket(QString);
protected:
    void showEvent(QShowEvent *event);

private slots:
    void onHeaderClicked(int,int);

    void on_btn_changed_clicked();

    void on_btn_delete_clicked();
 void acceptSocketData(QString);
private:
    int selectrow;
    Ui::ChildWidgetC *ui;
};

#endif // CHILDWIDGETC_H
