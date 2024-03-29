﻿#pragma execution_character_set("utf-8")
#include "registerstudentwidget.h"
#include "ui_registerstudentwidget.h"
#include "qxmessagebox/qxmessagebox.h"
#include "mainwidget.h"
#include <QRegExpValidator>

RegisterStudentWidget::RegisterStudentWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterStudentWidget)
{
    ui->setupUi(this);
    MainWidget::allSignalEvent.setRegisterStudentWidget(this);
    MainWidget::allSignalEvent.connectAllStudentSignal();
    setWindowTitle("注册学生信息");
    QRegExp regExpage("^[0-9]{1,2}$");
    QRegExp regExpnum("^[0-9]{1,10}$");
    QRegExp regExppass("^[a-zA-Z0-9]{1,10}$");
    QRegExp regExpname("^[a-zA-Z0-9_\u4e00-\u9fa5]{1,10}$");
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
    ui->lineEdit_8->setValidator(new QRegExpValidator(regExplevel));

}

RegisterStudentWidget::~RegisterStudentWidget()
{
    delete ui;
}

void RegisterStudentWidget::on_btn_resiger_clicked()
{
    QString tstr1 = ui->lineEdit_1->text();
    QString tstr2 = ui->lineEdit_2->text();
    QString tstr3 = ui->lineEdit_3->text();
    QString tstr4 = ui->comboBox->currentText();
    QString tstr5 = ui->lineEdit_5->text();
    QString tstr6 = ui->lineEdit_6->text();
    QString tstr7 = ui->lineEdit_7->text();
    QString tstr8 = ui->lineEdit_8->text();


    QString insertser = QString("insert into student_information values('%1','%2','%3','%4','%5','%6','%7','%8')")
            .arg(tstr1).arg(tstr3).arg(tstr2)
            .arg(tstr4).arg(tstr5).arg(tstr6)
            .arg(tstr7).arg(tstr8);
    QString strsend =  "RegisterStudent:" + insertser;
    emit sendWriteSocket(strsend);



}

void RegisterStudentWidget::on_btn_quit_clicked()
{
    done(0);
}

void RegisterStudentWidget::acceptSocketData(QString ret)
{
    if (ret == "false"){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("注册失败!");
        message.exec();
    }else{
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("注册成功!");
        message.exec();
    }
}
