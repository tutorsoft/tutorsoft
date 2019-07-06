#pragma execution_character_set("utf-8")
#include "childwidgetb.h"
#include "ui_childwidgetb.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../signalmanageobject/signalmanageobject.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"



ChildWidgetB::ChildWidgetB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetB)
{
    ui->setupUi(this);
    MainWidget::allSignalEvent.setChildWidgetB(this);

}

ChildWidgetB::~ChildWidgetB()
{
    delete ui;
}

void ChildWidgetB::on_btn_resiger_clicked()
{
    QString user = MainWidget::currentuser;
    QString tstr0 = "need_information";
    QString tstr1 = ui->lineEdit_1->text();
    QString tstr2 = ui->lineEdit_2->text();
    QString tstr3 = ui->lineEdit_3->text();
    QString tstr4 = ui->lineEdit_4->text();
    QString tstr5 = ui->lineEdit_5->text();
    QString tstr6 = ui->lineEdit_6->text();
    QString tstr7 = ui->lineEdit_7->text();
    QString tstr8 = ui->textEdit->toPlainText();

    QString insertser = QString("insert into %1 values('%2','%3','%4','%5','%6','%7','%8','%9','%10',' ')")
            .arg(tstr0).arg(tstr1).arg(tstr2).arg(tstr3)
            .arg(tstr4).arg(tstr5).arg(tstr6).arg(tstr7).arg(tstr8).arg(user);

    QString strsend =  "ChildWidgetB:" + insertser;
    emit sendWriteSocket(strsend);


}

void ChildWidgetB::acceptSocketData(QString ret)
{
    if (ret == "false"){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("发布失败!");
        message.exec();
    }else{
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("发布成功!");
        message.exec();
    }
}
