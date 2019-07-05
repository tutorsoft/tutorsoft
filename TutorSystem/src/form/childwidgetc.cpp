#pragma execution_character_set("utf-8")
#include "childwidgetc.h"
#include "ui_childwidgetc.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../database/userdatabase.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"


ChildWidgetC::ChildWidgetC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetC)
{
    ui->setupUi(this);
    selectrow = 0;
    QStringList header;
    header << "编号" << "需求名称"<<"科目"<<"开始时间"<<"结束时间"<<"费用"<<"年级"<<"需求说明"<<"教师姓名";
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tableWidget->horizontalHeader()->setFixedHeight(50);
    ui->tableWidget->horizontalHeader()->resizeSection(0,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(1,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(2,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(3,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(4,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(5,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(6,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(7,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(8,ui->tableWidget->width()*0.2);
    ui->tableWidget->horizontalHeader()->setStyleSheet(TAB_WIDGET_STYLE);

    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);
    updateDisplay();

    connect(ui->tableWidget, SIGNAL(cellClicked(int , int )),
            this, SLOT(onHeaderClicked(int,int)));

}

ChildWidgetC::~ChildWidgetC()
{
    delete ui;
}

void ChildWidgetC::showEvent(QShowEvent *event)
{   
    updateDisplay();     //将数据库中的需求信息显示出来
}

void ChildWidgetC::updateDisplay()
{
    QString tstr0 = "student_" + MainWidget::currentuser + "_information";
    ui->tableWidget->clearContents();
    QVector<QVector<QString>>  allinfo = queryAll(tstr0);   //获取指定数据库
    ui->tableWidget->setRowCount(allinfo.size());           //动态插入多行
    for(int i =0;i < allinfo.size();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(allinfo.at(i).at(0)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(allinfo.at(i).at(1)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(allinfo.at(i).at(2)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(allinfo.at(i).at(3)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(allinfo.at(i).at(4)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(allinfo.at(i).at(5)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(allinfo.at(i).at(6)));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(allinfo.at(i).at(7)));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(allinfo.at(i).at(8)));     //将数据库中的信息展示出来
    }
}

QVector<QVector<QString> > ChildWidgetC::queryAll(QString tablename)
{
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }
    QSqlQuery query(userDataBasePri::database);
    QString statement = QString("SELECT * FROM %1").arg(tablename);                 //查询数据表所有信息
    query.exec(statement);                                                          //执行命令
    QVector<QVector<QString>> retvector;
    QVector<QString> vectorstr;
    int midsize = 0;
    while(query.next())                                                             //搜索到信息则继续
    {
        vectorstr.clear();
        midsize = query.size();
        for(int i = 0; i < 40;i++ ){
            vectorstr.append(query.value(i).toByteArray());
        }
        retvector.append(vectorstr);                                                //将搜索到的信息添加到容器里（跟之前一样）
    }
    userDataBasePri::database.close();
    return retvector;                                                               //关闭数据库，返回容器
}

void ChildWidgetC::onHeaderClicked(int row,int column)
{
    selectrow = row;
    ui->lineEdit_1->setText(ui->tableWidget->item(row,0)->text());
    ui->lineEdit_2->setText(ui->tableWidget->item(row,1)->text());
    ui->lineEdit_3->setText(ui->tableWidget->item(row,2)->text());
    ui->lineEdit_4->setText(ui->tableWidget->item(row,3)->text());
    ui->lineEdit_5->setText(ui->tableWidget->item(row,4)->text());
    ui->lineEdit_6->setText(ui->tableWidget->item(row,5)->text());
    ui->lineEdit_7->setText(ui->tableWidget->item(row,6)->text());
    ui->textEdit->setText(ui->tableWidget->item(row,7)->text());                    //取出指定行编辑的内容并保存

}

void ChildWidgetC::on_btn_changed_clicked()
{
    QString tstr0 = "student_" + MainWidget::currentuser + "_information";
    QString tstr1 = ui->lineEdit_1->text();
    QString tstr2 = ui->lineEdit_2->text();
    QString tstr3 = ui->lineEdit_3->text();
    QString tstr4 = ui->lineEdit_4->text();
    QString tstr5 = ui->lineEdit_5->text();
    QString tstr6 = ui->lineEdit_6->text();
    QString tstr7 = ui->lineEdit_7->text();
    QString tstr8 = ui->textEdit->toPlainText();                                 //修改、输入信息（获取当前的输入框里字符）与之前一样

    if (! userDataBasePri::database.open()){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("数据库链接失败!");
        message.exec();
        qCritical() << userDataBasePri::database.lastError().text();
        return;
    }
    QSqlQuery query(userDataBasePri::database);

    QString updataStr = QString("update %1 set need_name = '%3' "
                                ", course = '%4' "
                                ", start_time = '%5' "
                                ", stop_time = '%6' "
                                ", cost = '%7' "
                                ", needgrade = '%8' "
                                ", needstr = '%9' "
                                "where needid = %2")
            .arg(tstr0).arg(tstr1).arg(tstr2).arg(tstr3)
            .arg(tstr4).arg(tstr5).arg(tstr6).arg(tstr7).arg(tstr8);

    bool ret = query.exec(updataStr);                                          //执行命令，更新需求信息
    qDebug()<<"asdfasdf"<<userDataBasePri::database.lastError().text();
    if (ret == false){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("更新失败!");
        message.exec();
    }else{
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("更新成功!");
        message.exec();
    }
    userDataBasePri::database.close();
}

void ChildWidgetC::on_btn_delete_clicked()
{
    QString tstr0 = "student_" + MainWidget::currentuser + "_information";
    QTableWidgetItem *t_item = ui->tableWidget->item(selectrow,0);
    QString t_text = t_item->text();
    qDebug()<<"t_item"<<t_text;

    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
        return;
    }
    QSqlQuery query(userDataBasePri::database);
    bool ret = query.exec(QString::fromLocal8Bit("delete from %1 where needid = %2").arg(tstr0).arg(t_text));
    qDebug()<<ret;
    userDataBasePri::database.close();
    updateDisplay();
}
