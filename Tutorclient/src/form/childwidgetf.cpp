#pragma execution_character_set("utf-8")
#include "childwidgetf.h"
#include "ui_childwidgetf.h"
#include "qfinddialog.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../signalmanageobject/signalmanageobject.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"

ChildWidgetF::ChildWidgetF(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetF)
{
    ui->setupUi(this);
    MainWidget::allSignalEvent.setChildWidgetF(this);
    selectrow = 0;
    QStringList header;
    header << "教师编号" << "教师名称"<<"教学年级";
    ui->tableWidget->setColumnCount(3);
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

ChildWidgetF::~ChildWidgetF()
{
    delete ui;
}

void ChildWidgetF::showEvent(QShowEvent *event)
{
    QString strsend =  "ChildWidgetF_queryAll:teacher_information";
    emit sendWriteSocket(strsend);
}

void ChildWidgetF::updateDisplay()
{
    ui->tableWidget->clearContents();
    QVector<QVector<QString>>  allinfo = queryAll("teacher_information");
    int num = 0;
    for(int i =0;i < allinfo.size();i++){
        if(allinfo.at(i).at(7) == "高中"){
            num++;
        }
    }
    ui->tableWidget->setRowCount(num);
    num = 0;
    for(int i =0;i < allinfo.size();i++){
        if(allinfo.at(i).at(7) == "高中"){
            ui->tableWidget->setItem(num,0,new QTableWidgetItem(allinfo.at(i).at(0)));
            ui->tableWidget->setItem(num,1,new QTableWidgetItem(allinfo.at(i).at(2)));
            ui->tableWidget->setItem(num++,2,new QTableWidgetItem(allinfo.at(i).at(7)));
        }
    }
}

QVector<QVector<QString> > ChildWidgetF::queryAll(QString tablename)
{
    QVector<QVector<QString>> retvector;
    return retvector;
}

void ChildWidgetF::onHeaderClicked(int row,int column)
{
    selectrow = row;
    ui->lineEdit->setText(ui->tableWidget->item(row,0)->text());
}

void ChildWidgetF::on_btn_find_clicked()
{

}

void ChildWidgetF::on_btn_look_clicked()
{
    QStringList strlist;
    QVector<QVector<QString>>  allinfo = queryAll("teacher_information");
//    for(int i =0;i < allinfo.size();i++){
//        if(allinfo.at(i).at(0) == ui->lineEdit->text()){
//            strlist.append(allinfo.at(i).at(0));
//            strlist.append(allinfo.at(i).at(2));
//            strlist.append(allinfo.at(i).at(3));
//            strlist.append(allinfo.at(i).at(4));
//            strlist.append(allinfo.at(i).at(5));
//            strlist.append(allinfo.at(i).at(6));
//            strlist.append(allinfo.at(i).at(7));
//            strlist.append(allinfo.at(i).at(8));
//        }
//    }
    QFindDialog w;
    w.setAllInfo(strlist);
    w.exec();
}

void ChildWidgetF::acceptSocketData(QString ret)
{
    qDebug()<<"ChildWidgetF==>"<<ret;
    QStringList tlist = ret.split(":");
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
    }
}
