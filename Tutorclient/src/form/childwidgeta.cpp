#pragma execution_character_set("utf-8")
#include "childwidgeta.h"
#include "ui_childwidgeta.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../signalmanageobject/signalmanageobject.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"

ChildWidgetA::ChildWidgetA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetA)
{
    ui->setupUi(this);
    ui->lineEdit_1->setEnabled(false);
    MainWidget::allSignalEvent.setChildWidgetA(this);
}

ChildWidgetA::~ChildWidgetA()
{
    delete ui;
}

void ChildWidgetA::showEvent(QShowEvent *event)
{
    QString strs = MainWidget::currentuser;
    QString strsend =  "ChildWidgetA_queryAll:student_information:" + strs;
    emit sendWriteSocket(strsend);
}

void ChildWidgetA::on_btn_resiger_clicked()
{
    QString tstr1 = ui->lineEdit_1->text();
    QString tstr2 = ui->lineEdit_2->text();
    QString tstr3 = ui->lineEdit_3->text();
    QString tstr4 = ui->lineEdit_4->text();
    QString tstr5 = ui->lineEdit_5->text();
    QString tstr6 = ui->lineEdit_6->text();
    QString tstr7 = ui->lineEdit_7->text();
    QString tstr8 = ui->lineEdit_8->text();

    QString updataStr = QString("update student_information set student_name = '%3' "
                                ", student_password = '%2' "
                                ", student_sex = '%4' "
                                ", student_age = '%5' "
                                ", student_phone = '%6' "
                                ", student_email = '%7' "
                                ", student_class = '%8' "
                                "where studentid = '%1'")
            .arg(tstr1).arg(tstr2).arg(tstr3)
            .arg(tstr4).arg(tstr5).arg(tstr6)
            .arg(tstr7).arg(tstr8);
    QString strsend =  "ChildWidgetA:" + updataStr;
    emit sendWriteSocket(strsend);

}

void ChildWidgetA::acceptSocketData(QString ret)
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
        ui->lineEdit_2->setText(tlista.at(1));
        ui->lineEdit_3->setText(tlista.at(2));
        ui->lineEdit_4->setText(tlista.at(3));
        ui->lineEdit_5->setText(tlista.at(4));
        ui->lineEdit_6->setText(tlista.at(5));
        ui->lineEdit_7->setText(tlista.at(6));
        ui->lineEdit_8->setText(tlista.at(7));
    }
}

