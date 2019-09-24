#pragma execution_character_set("utf-8")
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>

SignalManageObject MainWidget::allSignalEvent;
QString MainWidget::currentuser = "user";
QString MainWidget::currentusername  = "user";;
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("Qt家教通系统");
    m_LoginWidget = new LoginWidget(this);
    m_TeacherWidget = new TeacherWidget(this);
    m_StudentWidget = new StudentWidget(this);
    ui->stackedWidget->addWidget(m_LoginWidget);
    ui->stackedWidget->addWidget(m_TeacherWidget);
    ui->stackedWidget->addWidget(m_StudentWidget);
    ui->stackedWidget->setCurrentWidget(m_LoginWidget);



    connect(m_StudentWidget,SIGNAL(sendQuit()),this,SLOT(acceptLogout()));
    connect(m_TeacherWidget,SIGNAL(sendQuit()),this,SLOT(acceptLogout()));

    tcpClient = new QTcpSocket(this);
    tcpClient->abort();
    tcpClient->connectToHost("127.0.0.1",6666);
    if (tcpClient->waitForConnected(1000))
    {
        qDebug()<<"连接成功";
    }else{
        qDebug()<<"连接失败";
    }
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readAllData()));
    MainWidget::allSignalEvent.setMainWidget(this);
    MainWidget::allSignalEvent.connectAllSignal();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::accpetLoginSignal(bool state)
{
    if(state == false){
        ui->stackedWidget->setCurrentWidget(m_StudentWidget);
    }else{
        ui->stackedWidget->setCurrentWidget(m_TeacherWidget);
    }
}

void MainWidget::acceptLogout()
{
    ui->stackedWidget->setCurrentWidget(m_LoginWidget);
}

void MainWidget::readAllData()
{
    QByteArray str = tcpClient->readAll();
    QString retstr(str);
    QStringList strlist = retstr.split(":");
    QString t_flog = strlist.at(0);
    if(t_flog == "login"){
        emit sendDataToLoginWidget(strlist.at(1));
    }else if(t_flog == "RegisterTeacher"){
        emit sendDataToTeacherWidget(strlist.at(1));
    }else if(t_flog == "RegisterStudent"){
        emit sendDataToStudentWidget(strlist.at(1));
    }else if(t_flog == "ChildWidgetA"){
        emit sendDataToWidgetA(strlist.at(1));
    }else if(t_flog == "ChildWidgetB"){
        emit sendDataToWidgetB(strlist.at(1));
    }else if(t_flog == "ChildWidgetC"){
        emit sendDataToWidgetC(strlist.at(1));
    }else if(t_flog == "ChildWidgetG"){
        emit sendDataToWidgetG(strlist.at(1));
    }else if(t_flog == "ChildWidgetH"){
        emit sendDataToWidgetH(strlist.at(1));
    }else if(t_flog == "ChildWidgetI"){
        emit sendDataToWidgetI(strlist.at(1));
    }else if(t_flog == "ChildWidgetJ"){
        emit sendDataToWidgetJ(strlist.at(1));
    }else if(t_flog == "ChildWidgetK"){
        emit sendDataToWidgetK(strlist.at(1));
    }else if(t_flog == "EvaluateWidget"){
        emit sendEvaluateWidget(strlist.at(1));
    }else if(t_flog == "ChildWidgetA_queryAll"){
        emit sendDataToWidgetA(strlist.at(1));
    }else if(t_flog == "ChildWidgetC_queryAll"){
        emit sendDataToWidgetC(strlist.at(1) +":"+ strlist.at(2));
    }else if(t_flog == "ChildWidgetG_queryAll"){
        emit sendDataToWidgetG(strlist.at(1));
    }else if(t_flog == "ChildWidgetD_queryAll"){
        emit sendDataToWidgetD(strlist.at(1) +":"+ strlist.at(2));
    }else if(t_flog == "ChildWidgetE_queryAll"){
        emit sendDataToWidgetE(strlist.at(1) +":"+ strlist.at(2));
    }else if(t_flog == "ChildWidgetF_queryAll"){
        emit sendDataToWidgetF(strlist.at(1) +":"+ strlist.at(2));
    }else if(t_flog == "ChildWidgetH_queryAll"){
        emit sendDataToWidgetH(strlist.at(1) +":"+ strlist.at(2));
    }else if(t_flog == "ChildWidgetI_queryAll"){
        emit sendDataToWidgetI(strlist.at(1) +":"+ strlist.at(2));
    }else if(t_flog == "ChildWidgetJ_queryAll"){
        emit sendDataToWidgetJ(strlist.at(1) +":"+ strlist.at(2));
    }else if(t_flog == "ChildWidgetK_queryAll"){
        emit sendDataToWidgetK(strlist.at(1) +":"+ strlist.at(2));
    }else if(t_flog == "EvaluateWidget_queryAll"){
        emit sendEvaluateWidget(strlist.at(1) +":"+ strlist.at(2));
    }


}

void MainWidget::writeDataToSocket(QString str)
{
    qDebug()<<"ChildWidgetA_queryAll"<<str;
    tcpClient->write(str.toStdString().c_str());
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

}


