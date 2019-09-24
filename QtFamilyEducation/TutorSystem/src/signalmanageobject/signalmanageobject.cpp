#include "signalmanageobject.h"
#include "../mainwidget.h"
#include "../studentwidget.h"
#include "../loginwidget.h"
#include "../registerstudentwidget.h"
#include "../registerteacherwidget.h"
#include "../teacherwidget.h"
#include "../form/childwidgeta.h"
#include "../form/childwidgetb.h"
#include "../form/childwidgetc.h"
#include "../form/childwidgetd.h"
#include "../form/childwidgete.h"
#include "../form/childwidgetf.h"
#include "../form/childwidgetg.h"
#include "../form/childwidgeth.h"
#include "../form/childwidgeti.h"
#include "../form/childwidgetj.h"
#include "../form/childwidgetk.h"
#include "../form/evaluatewidget.h"

#define T_MainWidget(o)       (( MainWidget *)o)
#define T_LoginWidget(o)       (( LoginWidget *)o)
#define T_TeacherWidget(o)       (( TeacherWidget *)o)
#define T_StudentWidget(o)       (( StudentWidget *)o)
#define T_RegisterStudentWidget(o)       (( RegisterStudentWidget *)o)
#define T_RegisterTeacherWidget(o)       (( RegisterTeacherWidget *)o)
#define T_EvaluateWidget(o)       (( EvaluateWidget *)o)

#define T_ChildWidgetA(o)       (( ChildWidgetA *)o)
#define T_ChildWidgetB(o)       (( ChildWidgetB *)o)
#define T_ChildWidgetC(o)       (( ChildWidgetC *)o)
#define T_ChildWidgetD(o)       (( ChildWidgetD *)o)
#define T_ChildWidgetE(o)       (( ChildWidgetE *)o)
#define T_ChildWidgetF(o)       (( ChildWidgetF *)o)
#define T_ChildWidgetG(o)       (( ChildWidgetG *)o)
#define T_ChildWidgetH(o)       (( ChildWidgetH *)o)
#define T_ChildWidgetI(o)       (( ChildWidgetI *)o)
#define T_ChildWidgetJ(o)       (( ChildWidgetJ *)o)
#define T_ChildWidgetK(o)       (( ChildWidgetK *)o)

SignalManageObject::SignalManageObject(QObject *parent) : QObject(parent)
{

}

void SignalManageObject::connectAllSignal()
{
    if(m_MainWidget != NULL && m_LoginWidget != NULL){
        connect(T_LoginWidget(m_LoginWidget),SIGNAL(sendLoginSignal(bool)),T_MainWidget(m_MainWidget),SLOT(accpetLoginSignal(bool)));
    }
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetA(QString)),T_ChildWidgetA(m_ChildWidgetA),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetB(QString)),T_ChildWidgetB(m_ChildWidgetB),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetC(QString)),T_ChildWidgetC(m_ChildWidgetC),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetD(QString)),T_ChildWidgetD(m_ChildWidgetD),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetE(QString)),T_ChildWidgetE(m_ChildWidgetE),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetF(QString)),T_ChildWidgetF(m_ChildWidgetF),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetG(QString)),T_ChildWidgetG(m_ChildWidgetG),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetH(QString)),T_ChildWidgetH(m_ChildWidgetH),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetI(QString)),T_ChildWidgetI(m_ChildWidgetI),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetJ(QString)),T_ChildWidgetJ(m_ChildWidgetJ),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToWidgetK(QString)),T_ChildWidgetK(m_ChildWidgetK),SLOT(acceptSocketData(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToLoginWidget(QString)),T_LoginWidget(m_LoginWidget),SLOT(acceptSocketData(QString)));

    connect(T_ChildWidgetB(m_ChildWidgetA),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetB(m_ChildWidgetB),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetC(m_ChildWidgetC),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetD(m_ChildWidgetD),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetE(m_ChildWidgetE),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetF(m_ChildWidgetF),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetG(m_ChildWidgetG),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetH(m_ChildWidgetH),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetI(m_ChildWidgetI),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetJ(m_ChildWidgetJ),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_ChildWidgetK(m_ChildWidgetK),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_LoginWidget(m_LoginWidget),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));

}

void SignalManageObject::connectAllStudentSignal()
{
    connect(T_RegisterStudentWidget(m_RegisterStudentWidget),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToStudentWidget(QString)),T_RegisterStudentWidget(m_RegisterStudentWidget),SLOT(acceptSocketData(QString)));

}

void SignalManageObject::connectAllTeacherSignal()
{
    connect(T_RegisterTeacherWidget(m_RegisterTeacherWidget),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendDataToTeacherWidget(QString)),T_RegisterTeacherWidget(m_RegisterTeacherWidget),SLOT(acceptSocketData(QString)));

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

void SignalManageObject::setChildWidgetA(QWidget *w)
{
    m_ChildWidgetA = w;
}

void SignalManageObject::setChildWidgetB(QWidget *w)
{
    m_ChildWidgetB = w;
}

void SignalManageObject::setChildWidgetC(QWidget *w)
{
    m_ChildWidgetC = w;
}

void SignalManageObject::setChildWidgetD(QWidget *w)
{
    m_ChildWidgetD = w;
}

void SignalManageObject::setChildWidgetE(QWidget *w)
{
    m_ChildWidgetE = w;
}

void SignalManageObject::setChildWidgetF(QWidget *w)
{
    m_ChildWidgetF = w;
}

void SignalManageObject::setChildWidgetG(QWidget *w)
{
    m_ChildWidgetG = w;
}

void SignalManageObject::setChildWidgetH(QWidget *w)
{
    m_ChildWidgetH = w;
}

void SignalManageObject::setChildWidgetI(QWidget *w)
{
    m_ChildWidgetI = w;
}

void SignalManageObject::setChildWidgetJ(QWidget *w)
{
    m_ChildWidgetJ = w;
}

void SignalManageObject::setChildWidgetK(QWidget *w)
{
    m_ChildWidgetK = w;
}

void SignalManageObject::setEvaluateWidget(QWidget *w)
{
    m_EvaluateWidget = w;
    connect(T_MainWidget(m_MainWidget),SIGNAL(sendEvaluateWidget(QString)),T_EvaluateWidget(m_EvaluateWidget),SLOT(acceptSocketData(QString)));
    connect(T_EvaluateWidget(m_EvaluateWidget),SIGNAL(sendWriteSocket(QString)),T_MainWidget(m_MainWidget),SLOT(writeDataToSocket(QString)));
}



