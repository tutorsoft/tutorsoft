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

signals:
    void sendWriteSocket(QString);
private slots:
    void on_btn_resiger_clicked();

    void acceptSocketData(QString);


private:
    Ui::ChildWidgetA *ui;
};

#endif // CHILDWIDGETA_H
