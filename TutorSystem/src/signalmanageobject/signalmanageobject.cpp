#include "signalmanageobject.h"
#include "../mainwidget.h"
#include "../studentwidget.h"
#include "../registerstudentwidget.h"
#include "../registerteacherwidget.h"
#include "../teacherwidget.h"


#define T_MainWidget(o)       (( MainWidget *)o)
#define T_LoginWidget(o)       (( LoginWidget *)o)
#define T_TeacherWidget(o)       (( TeacherWidget *)o)
#define T_StudentWidget(o)       (( StudentWidget *)o)
#define T_RegisterStudentWidget(o)       (( RegisterStudentWidget *)o)
#define T_RegisterTeacherWidget(o)       (( RegisterTeacherWidget *)o)

SignalManageObject::SignalManageObject(QObject *parent) : QObject(parent)
{

}

void SignalManageObject::connectAllSignal()
{
    if(m_MainWidget != NULL && m_LoginWidget != NULL){
        connect(T_LoginWidget(m_LoginWidget),SIGNAL(sendLoginSignal(bool)),T_MainWidget(m_MainWidget),SLOT(accpetLoginSignal(bool)));
    }
}

void SignalManageObject::setMainWidget(QWidget *w)
{
    m_MainWidget = w;
}

void SignalManageObject::setLoginWidget(QWidget *w)
{
    m_LoginWidget = w;
}

void SignalManageObject::setTeacherWidget(QWidget *w)
{
    m_TeacherWidget = w;
}

void SignalManageObject::setStudentWidget(QWidget *w)
{
    m_StudentWidget = w;
}

void SignalManageObject::setRegisterTeacherWidget(QWidget *w)
{
    m_RegisterTeacherWidget = w;
}

void SignalManageObject::setRegisterStudentWidget(QWidget *w)
{
    m_RegisterStudentWidget = w;
}



