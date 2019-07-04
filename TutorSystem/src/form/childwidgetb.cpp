#pragma execution_character_set("utf-8")
#include "childwidgetb.h"
#include "ui_childwidgetb.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../database/userdatabase.h"
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

}

ChildWidgetB::~ChildWidgetB()
{
    delete ui;
}

void ChildWidgetB::on_btn_resiger_clicked()
{
    QString tstr0 = "student_" + MainWidget::currentuser + "_information";  //学生+主窗口小部件：：当前用户+信息
    QString tstr1 = ui->lineEdit_1->text();     //编号   输入信息（获取当前的输入框里字符）
    QString tstr2 = ui->lineEdit_2->text();     //需求名称
    QString tstr3 = ui->lineEdit_3->text();     //科目
    QString tstr4 = ui->lineEdit_4->text();     //开始时间
    QString tstr5 = ui->lineEdit_5->text();     //结束时间
    QString tstr6 = ui->lineEdit_6->text();     //费用
    QString tstr7 = ui->lineEdit_7->text();     //年级
    QString tstr8 = ui->textEdit->toPlainText();

    if (! userDataBasePri::database.open()){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("数据库链接失败!");
        message.exec();
        qCritical() << userDataBasePri::database.lastError().text();
        return;
    }
    QSqlQuery query(userDataBasePri::database);

    QString insertser = QString("insert into %1 values('%2','%3','%4','%5','%6','%7','%8','%9',' ')")
            .arg(tstr0).arg(tstr1).arg(tstr3).arg(tstr2)
            .arg(tstr4).arg(tstr5).arg(tstr6).arg(tstr7).arg(tstr8);  //用字符串变量参数依次替代字符串中最小数值

    bool ret = query.exec(insertser);           //向表中插入信息
    if (ret == false){//打开数据库
        qDebug()<<"query"<<query.lastError();
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
    userDataBasePri::database.close();

}
