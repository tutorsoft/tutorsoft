#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpserver.h"
#include "childwidgeta.h"
#include "childwidgetb.h"
#include "childwidgetc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void acceptClientInfo(int handle, QString ip, int prot);
    void acceptClientData(int,quint16,QByteArray );


    void on_btn_stutent_clicked();

    void on_btn_teacher_clicked();

private:
    Ui::MainWindow *ui;
    TcpServer ser;
    ChildWidgetA *m_ChildWidgetA;
    ChildWidgetB *m_ChildWidgetB;
    ChildWidgetC *m_ChildWidgetC;
};

#endif // MAINWINDOW_H
