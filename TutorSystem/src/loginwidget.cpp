#pragma execution_character_set("utf-8")
#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "mainwidget.h"
#include "qxmessagebox/qxmessagebox.h"
#include "database/userdatabase.h"
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
        if (! userDataBasePri::database.open()){//打开数据库
            QXMessageBox message;
            message.setlabelTitleStr("提示!");
            message.setlabelMsgStr("数据库链接失败!");
            message.exec();
            qCritical() << userDataBasePri::database.lastError().text();
            return;
        }
        QSqlQuery query(userDataBasePri::database);
        if(combox == 0){
            bool ret = query.exec(QString::fromLocal8Bit("select * from teacher_information where teacherid = '%1'").arg(user));
            QString t_password;
            QString t_root;
            while (query.next()){
                t_password = query.value(1).toString();
                t_root = query.value(2).toString();
            }
            if(password == t_password){
                emit sendLoginSignal(true);
            }else{
                QXMessageBox message;
                message.setlabelTitleStr("提示!");
                message.setlabelMsgStr("用户名或密码不匹配!");
                message.exec();
            }
        }else{
            bool ret = query.exec(QString::fromLocal8Bit("select * from student_information where studentid = '%1'").arg(user));
            QString t_password;
            QString t_root;
            while (query.next()){
                t_password = query.value(1).toString();
                t_root = query.value(2).toString();
            }
            if(password == t_password){
                emit sendLoginSignal(false);
            }else{
                QXMessageBox message;
                message.setlabelTitleStr("提示!");
                message.setlabelMsgStr("用户名或密码不匹配!");
                message.exec();
            }
        }
        userDataBasePri::database.close();
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
