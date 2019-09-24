#ifndef CHILDWIDGETK_H
#define CHILDWIDGETK_H

#include <QWidget>

namespace Ui {
class ChildWidgetK;
}

class ChildWidgetK : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetK(QWidget *parent = 0);
    ~ChildWidgetK();
signals:
    void sendWriteSocket(QString);
protected:
    void showEvent(QShowEvent *event);

private slots:
    void onHeaderClicked(int,int);

    void acceptSocketData(QString);
private:
    Ui::ChildWidgetK *ui;
    int selectrow;
};

#endif // CHILDWIDGETK_H
