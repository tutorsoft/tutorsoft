#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "loginwidget.h"
#include "signalmanageobject/signalmanageobject.h"
#include "database/userdatabase.h"
#include "studentwidget.h"
#include "teacherwidget.h"

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

};

#endif // MAINWIDGET_H
