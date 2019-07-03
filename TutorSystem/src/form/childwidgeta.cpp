#pragma execution_character_set("utf-8")
#include "childwidgeta.h"
#include "ui_childwidgeta.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../database/userdatabase.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"

ChildWidgetA::ChildWidgetA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetA)
{
    ui->setupUi(this);//setupUi(this)是由.ui文件生成的类的构造函数，这个函数的作用是对界面进行初始化，它按照我们在Qt设计器里设计的样子把窗体画出来，把我们在Qt设计器里面定义的信号和槽建立起来。
                      //也可以说，setupUi是我们画界面和写程序之间的桥梁。
    ui->lineEdit_1->setEnabled(false);//.lineedit不可修改，内容变成灰色
}

ChildWidgetA::~ChildWidgetA()
{
    delete ui;//析构函数，在析构的时候delete掉ui，ui是系统根据界面ui文件自动生成的ui类创建的对象，作为窗口serial类的成员
}

void ChildWidgetA::showEvent(QShowEvent *event)
{
    QVector<QVector<QString>>  allinfo = queryAll("student_information");
    for(int i =0;i < allinfo.size();i++){
        if(MainWidget::currentuser == allinfo.at(i).at(0)){
            ui->lineEdit_1->setText(allinfo.at(i).at(0));
            ui->lineEdit_2->setText(allinfo.at(i).at(1));
            ui->lineEdit_3->setText(allinfo.at(i).at(2));
            ui->lineEdit_4->setText(allinfo.at(i).at(3));
            ui->lineEdit_5->setText(allinfo.at(i).at(4));
            ui->lineEdit_6->setText(allinfo.at(i).at(5));
            ui->lineEdit_7->setText(allinfo.at(i).at(6));
            ui->lineEdit_8->setText(allinfo.at(i).at(7));      //提供数据表名，获取其中的个人信息，并显示出来
        }
    }
}

QVector<QVector<QString>> ChildWidgetA::queryAll(QString tablename)
{
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }
    QSqlQuery query(userDataBasePri::database);
    QString statement = QString("SELECT * FROM %1").arg(tablename);  //数据表名代入  即"SELECT * FROM 数据表名"
    query.exec(statement);  // 执行 “搜索指定的数据表的所有信息
    QVector<QVector<QString>> retvector;
    QVector<QString> vectorstr;
    int midsize = 0;
    while(query.next())//搜索到信息则继续——依次取出查询结果的每一条记录，直至结束，从数据库的开头一直往下找，如果某一行存了数据则返回1，如果是1个空行，则返回0
    {
        vectorstr.clear();
        midsize = query.size();
        for(int i = 0; i < 40;i++ ){
            vectorstr.append(query.value(i).toByteArray());//value(int n) ：获得属性的值。其中n表示你查询的第n个属性，0表示第一个。
        }
        retvector.append(vectorstr);    //将搜索到的信息添加到容器里
    }
    userDataBasePri::database.close();  //关闭数据库
    return retvector;                   //返回容器
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
    QString tstr8 = ui->lineEdit_8->text();    //修改、输入信息（获取当前的输入框里字符）

    if (! userDataBasePri::database.open()){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("数据库链接失败!");
        message.exec();
        qCritical() << userDataBasePri::database.lastError().text();
        return;
    }
    QSqlQuery query(userDataBasePri::database);

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
            .arg(tstr7).arg(tstr8);                           //命令


    query.exec(updataStr);                                //执行命令，更新学生信息

    bool ret = query.exec(updataStr);                     //执行成功返回真，反之假
    if (ret == false){//打开数据库                          //执行失败后打开数据库，并提示更新失败
        qDebug()<<"query"<<query.lastError();
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("更新失败!");
        message.exec();
    }else{                                                 //执行成功提示更新成功
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("更新成功!");
        message.exec();
    }
    userDataBasePri::database.close();
}
