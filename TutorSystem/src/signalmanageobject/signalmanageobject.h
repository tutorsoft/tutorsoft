#ifndef SIGNALMANAGEOBJECT_H
#define SIGNALMANAGEOBJECT_H

#include <QObject>
#include <QWidget>


class SignalManageObject : public QObject
{
    Q_OBJECT
public:
    explicit SignalManageObject(QObject *parent = 0);

    void connectAllSignal();

signals:

public slots:
    void setMainWidget(QWidget*);
    void setLoginWidget(QWidget*);
    void setTeacherWidget(QWidget*);
    void setStudentWidget(QWidget*);
    void setRegisterTeacherWidget(QWidget*);
    void setRegisterStudentWidget(QWidget*);

private:
    QWidget *m_MainWidget = NULL;
    QWidget *m_LoginWidget = NULL;
    QWidget *m_TeacherWidget = NULL;
    QWidget *m_StudentWidget = NULL;
    QWidget *m_RegisterTeacherWidget = NULL;
    QWidget *m_RegisterStudentWidget = NULL;

};

#endif // SIGNALMANAGEOBJECT_H
