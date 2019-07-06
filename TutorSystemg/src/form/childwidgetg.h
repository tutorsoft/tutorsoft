#ifndef CHILDWIDGETG_H
#define CHILDWIDGETG_H

#include <QWidget>

namespace Ui {
class ChildWidgetG;
}

class ChildWidgetG : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetG(QWidget *parent = 0);
    ~ChildWidgetG();
signals:
    void sendWriteSocket(QString);
protected:
    void showEvent(QShowEvent *event);
    QVector<QVector<QString>> queryAll(QString tablename);
private slots:
    void on_btn_resiger_clicked();
 void acceptSocketData(QString);
private:
    Ui::ChildWidgetG *ui;
};

#endif // CHILDWIDGETG_H
