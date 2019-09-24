#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "loginwidget.h"
#include "signalmanageobject/signalmanageobject.h"
#include "studentwidget.h"
#include "teacherwidget.h"
#include <QTcpSocket>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void accpetLoginSignal(bool);
    void acceptLogout();
    void readAllData();
    void writeDataToSocket(QString);

signals:
    void sendEvaluateWidget(QString);
    void sendDataToWidgetA(QString);
    void sendDataToWidgetB(QString);
    void sendDataToWidgetC(QString);
    void sendDataToWidgetD(QString);
    void sendDataToWidgetE(QString);
    void sendDataToWidgetF(QString);
    void sendDataToWidgetG(QString);
    void sendDataToWidgetH(QString);
    void sendDataToWidgetI(QString);
    void sendDataToWidgetJ(QString);
    void sendDataToWidgetK(QString);
    void sendDataToStudentWidget(QString);
    void sendDataToTeacherWidget(QString);
    void sendDataToLoginWidget(QString);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWidget *ui;
    LoginWidget *m_LoginWidget;
    TeacherWidget *m_TeacherWidget;
    StudentWidget *m_StudentWidget;

public:
    static SignalManageObject allSignalEvent;
    static QString currentuser;
    static QString currentusername;
    QTcpSocket * tcpClient;

};

#endif // MAINWIDGET_H
