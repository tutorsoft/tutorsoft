#pragma execution_character_set("utf-8")
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>

SignalManageObject MainWidget::allSignalEvent;
QString MainWidget::currentuser = "user";
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("家教通");

    userDataBasePri database;
    m_LoginWidget = new LoginWidget(this);
    m_TeacherWidget = new TeacherWidget(this);
    m_StudentWidget = new StudentWidget(this);
    ui->stackedWidget->addWidget(m_LoginWidget);
    ui->stackedWidget->addWidget(m_TeacherWidget);
    ui->stackedWidget->addWidget(m_StudentWidget);
    ui->stackedWidget->setCurrentWidget(m_LoginWidget);
    MainWidget::allSignalEvent.setMainWidget(this);
    MainWidget::allSignalEvent.connectAllSignal();

    connect(m_StudentWidget,SIGNAL(sendQuit()),this,SLOT(acceptLogout()));
    connect(m_TeacherWidget,SIGNAL(sendQuit()),this,SLOT(acceptLogout()));
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

void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    QPixmap foreImg;
//    foreImg.load(":/image/bga.png");
//    if (!foreImg.isNull())
//    {
//        painter.setOpacity(0.9);//透明度设置
//        painter.drawPixmap(0,0,this->width(),this->height(), foreImg);
//    }
}


