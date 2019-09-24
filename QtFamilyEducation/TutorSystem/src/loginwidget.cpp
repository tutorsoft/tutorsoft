#pragma execution_character_set("utf-8")
#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "mainwidget.h"
#include "qxmessagebox/qxmessagebox.h"
#include <QPainter>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    MainWidget::allSignalEvent.setLoginWidget(this);
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_btn_login_clicked()
{
    QString password = ui->password_lineEdit->text();
    QString user = ui->user_lineEdit->text();
    int combox = ui->comboBox->currentIndex();
    MainWidget::currentuser = user;

    if(user == "" || password == ""){
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("用户名或密码不能为空!");
        message.exec();
    }else{
        if(combox == 0){
            QString strsend =  "login:" + QString::fromLocal8Bit("select * from teacher_information where teacherid = '%1'").arg(user) +":" + password;
            emit sendWriteSocket(strsend);
        }else{
            QString strsend =  "login:" + QString::fromLocal8Bit("select * from student_information where studentid = '%1'").arg(user) +":" + password;
            emit sendWriteSocket(strsend);
        }
    }
}

void LoginWidget::on_btn_register_clicked()
{
    if(ui->comboBox->currentIndex() == 0){
        RegisterTeacherWidget w;
        w.exec();
    }else{
        RegisterStudentWidget w;
        w.exec();
    }
}

void LoginWidget::acceptSocketData(QString str)
{
    QStringList strlist = str.split("*");
     MainWidget::currentusername = strlist.at(1);
    qDebug()<<"acceptSocketData"<<str;
    if(strlist.at(0) == "true"){
        if(ui->comboBox->currentIndex() == 0){
            emit sendLoginSignal(true);
        }else{
            emit sendLoginSignal(false);
        }
    }else{
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("登录失败!");
        message.exec();
    }

}
