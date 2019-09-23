#pragma execution_character_set("utf-8")
#include "childwidgetg.h"
#include "ui_childwidgetg.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../signalmanageobject/signalmanageobject.h"
#include <QRegExpValidator>

ChildWidgetG::ChildWidgetG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetG)
{
    ui->setupUi(this);
    MainWidget::allSignalEvent.setChildWidgetG(this);
    QRegExp regExpage("^[0-9]{1,2}$");
    QRegExp regExpnum("^[0-9]{1,10}$");
    QRegExp regExppass("^[a-zA-Z0-9]{1,10}$");
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
    ui->lineEdit_8->setValidator(new QRegExpValidator(regExplevel));
}

ChildWidgetG::~ChildWidgetG()
{
    delete ui;
}

void ChildWidgetG::showEvent(QShowEvent *event)
{
    QString strs = MainWidget::currentuser;
    QString strsend =  "ChildWidgetG_queryAll:teacher_information:" + strs;
    emit sendWriteSocket(strsend);
}

QVector<QVector<QString>> ChildWidgetG::queryAll(QString tablename)
{
    QVector<QVector<QString>> retvector;
    return retvector;
}

void ChildWidgetG::on_btn_resiger_clicked()
{
    QString tstr1 = ui->lineEdit_1->text();
    QString tstr2 = ui->lineEdit_2->text();
    QString tstr3 = ui->lineEdit_3->text();
    QString tstr4 = ui->lineEdit_4->text();
    QString tstr5 = ui->lineEdit_5->text();
    QString tstr6 = ui->lineEdit_6->text();
    QString tstr7 = ui->lineEdit_7->text();
    QString tstr8 = ui->lineEdit_8->text();
    QString tstr9 = ui->lineEdit_9->text();


    QString updataStr = QString("update teacher_information set teacher_name = '%2' "
                                ", teacher_password = '%3' "
                                ", teacher_sex = '%4' "
                                ", teacher_age = '%5' "
                                ", teacher_phone = '%6' "
                                ", teacher_email = '%7' "
                                ", teacher_level = '%8' "
                                ", teacher_info = '%9' "
                                "where teacherid = '%1'")
            .arg(tstr1).arg(tstr2).arg(tstr3)
            .arg(tstr4).arg(tstr5).arg(tstr6)
            .arg(tstr7).arg(tstr8).arg(tstr9);
    QString strsend =  "ChildWidgetG:" + updataStr;
    emit sendWriteSocket(strsend);

}

void ChildWidgetG::acceptSocketData(QString ret)
{
    qDebug()<<"retstr==>"<<ret;
    QStringList tlist = ret.split(":");
    if (tlist.at(0) == "false"){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("更新失败!");
        message.exec();
    }else if (tlist.at(0) == "true"){
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("更新成功!");
        message.exec();
    }else{
        QStringList tlista = ret.split("+");
        ui->lineEdit_1->setText(tlista.at(0));
        ui->lineEdit_2->setText(tlista.at(2));
        ui->lineEdit_3->setText(tlista.at(1));
        ui->lineEdit_4->setText(tlista.at(3));
        ui->lineEdit_5->setText(tlista.at(4));
        ui->lineEdit_6->setText(tlista.at(5));
        ui->lineEdit_7->setText(tlista.at(6));
        ui->lineEdit_8->setText(tlista.at(7));
        ui->lineEdit_9->setText(tlista.at(8));
    }
}
