#pragma execution_character_set("utf-8")
#include "registerteacherwidget.h"
#include "ui_registerteacherwidget.h"
#include "qxmessagebox.h"
#include "userdatabase.h"
#include <QRegExpValidator>

RegisterTeacherWidget::RegisterTeacherWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterTeacherWidget)
{
    ui->setupUi(this);
    setWindowTitle("注册老师信息");
    QRegExp regExpage("^[0-9]{1,2}$");
    QRegExp regExpnum("^[0-9]{1,10}$");
    QRegExp regExppass("^[a-zA-Z0-9]{1,10}$");
    QRegExp regExpchar("^[a-zA-Z0-9_\u4e00-\u9fa5]{1,100}$");
    QRegExp regExpname("^[\u4e00-\u9fa5]{1,5}$");
    QRegExp regExpemail("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+$");
    QRegExp regExpsex("^[\u4e00-\u9fa5]{1,2}$");
    QRegExp regExplevel("^[\u4e00-\u9fa5]{1,5}$");
    QRegExp regExpphone("^[0-9]{1,12}$");

    ui->lineEdit_1->setValidator(new QRegExpValidator(regExpnum));
    ui->lineEdit_2->setValidator(new QRegExpValidator(regExpname));
    ui->lineEdit_3->setValidator(new QRegExpValidator(regExppass));
    ui->lineEdit_5->setValidator(new QRegExpValidator(regExpage));
    ui->lineEdit_6->setValidator(new QRegExpValidator(regExpphone));
    ui->lineEdit_7->setValidator(new QRegExpValidator(regExpemail));
    ui->lineEdit_9->setValidator(new QRegExpValidator(regExpchar));
}

RegisterTeacherWidget::~RegisterTeacherWidget()
{
    delete ui;
}

void RegisterTeacherWidget::on_btn_resiger_clicked()
{
    QString tstr1 = ui->lineEdit_1->text();
    QString tstr2 = ui->lineEdit_2->text();
    QString tstr3 = ui->lineEdit_3->text();
    QString tstr4 = ui->comboBox->currentText();
    QString tstr5 = ui->lineEdit_5->text();
    QString tstr6 = ui->lineEdit_6->text();
    QString tstr7 = ui->lineEdit_7->text();
    QString tstr8 = ui->comboBox_2->currentText();
    QString tstr9 = ui->lineEdit_9->text();

    if (! userDataBasePri::database.open()){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("数据库链接失败!");
        message.exec();
        qCritical() << userDataBasePri::database.lastError().text();
        return;
    }
    QSqlQuery query(userDataBasePri::database);

    QString insertser = QString("insert into teacher_information values('%1','%2','%3','%4','%5','%6','%7','%8','%9')")
            .arg(tstr1).arg(tstr3).arg(tstr2)
            .arg(tstr4).arg(tstr5).arg(tstr6)
            .arg(tstr7).arg(tstr8).arg(tstr9);
    bool ret = query.exec(insertser);
    if (ret == false){//打开数据库
        qDebug()<<"query"<<query.lastError();
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("注册失败!");
        message.exec();
    }else{
        //教师评价
        bool rets = query.exec(QString("create table %1(evaluateid varchar(20) primary key,evaluate_student varchar(20),evaluate_text varchar(100))").arg(QString("evaluate_%1").arg(tstr1)));
        rets = query.exec(QString("insert into %1 values('0001','张三','666')").arg(tstr1));

        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("注册成功!");
        message.exec();
    }
    userDataBasePri::database.close();
}

void RegisterTeacherWidget::on_btn_quit_clicked()
{
    done(0);
}
