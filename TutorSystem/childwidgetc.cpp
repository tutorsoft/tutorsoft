#pragma execution_character_set("utf-8")
#include "childwidgetc.h"
#include "ui_childwidgetc.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../signalmanageobject/signalmanageobject.h"
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
    MainWidget::allSignalEvent.setChildWidgetC(this);
    selectrow = 0;
    QStringList header;
    header << "编号" << "需求名称"<<"科目"<<"开始时间"<<"结束时间"<<"费用"<<"年级"<<"需求说明"<<"发布者姓名"<<"教师姓名";
    ui->tableWidget->setColumnCount(10);
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
    ui->tableWidget->horizontalHeader()->resizeSection(8,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(9,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->setStyleSheet(TAB_WIDGET_STYLE);

    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);

    connect(ui->tableWidget, SIGNAL(cellClicked(int , int )),
            this, SLOT(onHeaderClicked(int,int)));

}

ChildWidgetC::~ChildWidgetC()
{
    delete ui;
}

void ChildWidgetC::showEvent(QShowEvent *event)
{   
    QString tstr0 = "need_information";
    QString strsend =  "ChildWidgetC_queryAll:" + tstr0;
    emit sendWriteSocket(strsend);

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
    ui->textEdit->setText(ui->tableWidget->item(row,7)->text());

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
    QString tstr8 = ui->textEdit->toPlainText();

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
    QString strsend =  "ChildWidgetC:" + updataStr;
    emit sendWriteSocket(strsend);
}

void ChildWidgetC::on_btn_delete_clicked()
{
    QString tstr0 = "student_" + MainWidget::currentuser + "_information";
    QTableWidgetItem *t_item = ui->tableWidget->item(selectrow,0);
    QString t_text = t_item->text();
    qDebug()<<"t_item"<<t_text;

    QString deletestr = QString::fromLocal8Bit("delete from %1 where needid = %2").arg(tstr0).arg(t_text);
    QString strsend =  "ChildWidgetC:" + deletestr;
    emit sendWriteSocket(strsend);

}

void ChildWidgetC::acceptSocketData(QString ret)
{
    qDebug()<<"ChildWidgetC==>"<<ret;
    QStringList tlist = ret.split(":");
    if (tlist.at(0) == "false"){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("失败!");
        message.exec();
    }else if (tlist.at(0) == "true"){
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("成功!");
        message.exec();
    }else{
        ui->tableWidget->clearContents();
        QString num = tlist.at(0);
        QString data =  tlist.at(1);
        QStringList datalist = data.split("*");
        ui->tableWidget->setRowCount(num.toInt());

        for(int i = 0;i < datalist.size()-1;i++){
            QString indata = datalist.at(i);
            QStringList indatalist = indata.split("+");
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(indatalist.at(0)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(indatalist.at(1)));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(indatalist.at(2)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(indatalist.at(3)));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(indatalist.at(4)));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(indatalist.at(5)));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(indatalist.at(6)));
            ui->tableWidget->setItem(i,7,new QTableWidgetItem(indatalist.at(7)));
            ui->tableWidget->setItem(i,8,new QTableWidgetItem(indatalist.at(8)));
            ui->tableWidget->setItem(i,9,new QTableWidgetItem(indatalist.at(9)));
        }
    }
}
