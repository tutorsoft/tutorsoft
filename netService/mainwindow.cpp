#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include "userdatabase.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userDataBasePri database;
    setWindowTitle("服务器");

    m_ChildWidgetA = new ChildWidgetA(this);
    m_ChildWidgetB = new ChildWidgetB(this);
    m_ChildWidgetC = new ChildWidgetC(this);

    ui->stackedWidget->addWidget(m_ChildWidgetA);
    ui->stackedWidget->addWidget(m_ChildWidgetB);
    ui->stackedWidget->addWidget(m_ChildWidgetC);
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetA);
    //监听所有
    ser.listen(QHostAddress::Any,6666);
    connect(&ser, SIGNAL(connectClient(int,QString,int)), this, SLOT(acceptClientInfo(int, QString,int)));
    connect(&ser, SIGNAL(readData(int,quint16,QByteArray)), this, SLOT(acceptClientData(int,quint16,QByteArray)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::acceptClientInfo(int handle, QString ip, int prot)
{
    QString str = QString("handle:%1").arg(handle) + "  IP:" + ip + QString("  Port:%1").arg(prot);

}

void MainWindow::acceptClientData(int socktid, quint16 size, QByteArray buff)
{

}

void MainWindow::on_btn_stutent_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetA);
}

void MainWindow::on_btn_teacher_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetB);
}
