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
    void connectAllStudentSignal();
    void connectAllTeacherSignal();
signals:

public slots:
    void setMainWidget(QWidget*);
    void setLoginWidget(QWidget*);
    void setTeacherWidget(QWidget*);
    void setStudentWidget(QWidget*);
    void setRegisterTeacherWidget(QWidget*);
    void setRegisterStudentWidget(QWidget*);

    void setChildWidgetA(QWidget*);
    void setChildWidgetB(QWidget*);
    void setChildWidgetC(QWidget*);
    void setChildWidgetD(QWidget*);
    void setChildWidgetE(QWidget*);
    void setChildWidgetF(QWidget*);
    void setChildWidgetG(QWidget*);
    void setChildWidgetH(QWidget*);
    void setChildWidgetI(QWidget*);
    void setChildWidgetJ(QWidget*);
    void setChildWidgetK(QWidget*);
    void setEvaluateWidget(QWidget*);

private:
    QWidget *m_MainWidget = NULL;
    QWidget *m_LoginWidget = NULL;
    QWidget *m_TeacherWidget = NULL;
    QWidget *m_StudentWidget = NULL;
    QWidget *m_RegisterTeacherWidget = NULL;
    QWidget *m_RegisterStudentWidget = NULL;

    QWidget *m_ChildWidgetA = NULL;
    QWidget *m_ChildWidgetB = NULL;
    QWidget *m_ChildWidgetC = NULL;
    QWidget *m_ChildWidgetD = NULL;
    QWidget *m_ChildWidgetE = NULL;
    QWidget *m_ChildWidgetF = NULL;
    QWidget *m_ChildWidgetG = NULL;
    QWidget *m_ChildWidgetH = NULL;
    QWidget *m_ChildWidgetI = NULL;
    QWidget *m_ChildWidgetJ = NULL;
    QWidget *m_ChildWidgetK = NULL;
        QWidget *m_EvaluateWidget = NULL;


};

#endif // SIGNALMANAGEOBJECT_H
