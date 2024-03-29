﻿#pragma execution_character_set("utf-8")
#include "childwidgete.h"
#include "ui_childwidgete.h"
#include "qfinddialog.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../signalmanageobject/signalmanageobject.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"

ChildWidgetE::ChildWidgetE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetE)
{
    ui->setupUi(this);
    MainWidget::allSignalEvent.setChildWidgetE(this);
    selectrow = 0;
    QStringList header;
    header << "教师编号" << "教师名称"<<"教学年级";
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tableWidget->horizontalHeader()->setFixedHeight(50);
    ui->tableWidget->horizontalHeader()->resizeSection(0,ui->tableWidget->width()*0.4);
    ui->tableWidget->horizontalHeader()->resizeSection(1,ui->tableWidget->width()*0.3);
    ui->tableWidget->horizontalHeader()->resizeSection(2,ui->tableWidget->width()*0.3);
    ui->tableWidget->horizontalHeader()->setStyleSheet(TAB_WIDGET_STYLE);

    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);
    updateDisplay();

    connect(ui->tableWidget, SIGNAL(cellClicked(int , int )),
            this, SLOT(onHeaderClicked(int,int)));
}

ChildWidgetE::~ChildWidgetE()
{
    delete ui;
}

void ChildWidgetE::showEvent(QShowEvent *event)
{
    QString strsend =  "ChildWidgetE_queryAll:teacher_information";
    emit sendWriteSocket(strsend);
}

void ChildWidgetE::updateDisplay()
{

}

QVector<QVector<QString> > ChildWidgetE::queryAll(QString tablename)
{
    QVector<QVector<QString>> retvector;
    return retvector;
}

void ChildWidgetE::onHeaderClicked(int row,int column)
{
    selectrow = row;
    ui->lineEdit->setText(ui->tableWidget->item(row,0)->text());
}

void ChildWidgetE::acceptSocketData(QString ret)
{
    qDebug()<<"ChildWidgetE==="<<ret;
    QStringList tlist = ret.split(":");
    ui->tableWidget->clearContents();
    QString num = tlist.at(0);
    QString data =  tlist.at(1);
    datalist = data.split("*");
    ui->tableWidget->setRowCount(num.toInt());
  int numsd = 0;
    for(int i = 0;i < datalist.size()-1;i++){
        QString indata = datalist.at(i);
        QStringList indatalist = indata.split("+");
        if(indatalist.at(7) == "小学"){
            ui->tableWidget->setItem(numsd,0,new QTableWidgetItem(indatalist.at(0)));
            ui->tableWidget->setItem(numsd,1,new QTableWidgetItem(indatalist.at(2)));
            ui->tableWidget->setItem(numsd,2,new QTableWidgetItem(indatalist.at(7)));
        numsd++;
        }
    }
}

void ChildWidgetE::on_btn_find_clicked()
{

}

void ChildWidgetE::on_btn_look_clicked()
{
    QStringList strlist;
    for(int i = 0;i < datalist.size()-1;i++){
        QString indata = datalist.at(i);
        QStringList indatalist = indata.split("+");
        if(selectrow == i){
            strlist.append(indatalist.at(0));
            strlist.append(indatalist.at(2));
            strlist.append(indatalist.at(3));
            strlist.append(indatalist.at(4));
            strlist.append(indatalist.at(5));
            strlist.append(indatalist.at(6));
            strlist.append(indatalist.at(7));
            strlist.append(indatalist.at(8));
        }
    }
qDebug()<<"strlist--->"<<strlist;
    QFindDialog w;
    w.setAllInfo(strlist);
    w.exec();
}
