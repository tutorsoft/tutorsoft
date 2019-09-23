#pragma execution_character_set("utf-8")
#include "childwidgeti.h"
#include "ui_childwidgeti.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../signalmanageobject/signalmanageobject.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"


ChildWidgetI::ChildWidgetI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetI)
{
    ui->setupUi(this);
    MainWidget::allSignalEvent.setChildWidgetI(this);
    selectrow = 0;
    QStringList header;
    header <<"学生编号" << "编号" << "需求名称"<<"科目"<<"开始时间"<<"结束时间"<<"费用"<<"年级"<<"需求说明";
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

    connect(ui->tableWidget, SIGNAL(cellClicked(int , int )),
            this, SLOT(onHeaderClicked(int,int)));
}

ChildWidgetI::~ChildWidgetI()
{
    delete ui;
}

void ChildWidgetI::showEvent(QShowEvent *event)
{
    QString tstr0 = "need_information";
    QString strsend =  "ChildWidgetI_queryAll:" + tstr0;
    emit sendWriteSocket(strsend);
}

void ChildWidgetI::onHeaderClicked(int row,int column)
{
    selectrow = row;
}

void ChildWidgetI::on_btn_look_clicked()
{
    QString tstr0 = MainWidget::currentuser;
    QString tstr1 = ui->tableWidget->item(selectrow,0)->text();

    QString tstra = "need_information";
    QString updataStr =  QString::fromLocal8Bit("update %1 set acceptissuer = '%2' where needid = '%3'")
            .arg(tstra).arg(tstr0).arg(tstr1);
    QString strsend =  "ChildWidgetI:" + updataStr;
    emit sendWriteSocket(strsend);
}

void ChildWidgetI::acceptSocketData(QString ret)
{
    qDebug()<<"ChildWidgetI==>"<<ret;
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

        int numds = 0;
        for(int i = 0;i < datalist.size()-1;i++){
            QString indata = datalist.at(i);
            QStringList indatalist = indata.split("+");
            if(indatalist.at(6) == "初中"){
                ui->tableWidget->setItem(numds,0,new QTableWidgetItem(indatalist.at(8)));
                ui->tableWidget->setItem(numds,1,new QTableWidgetItem(indatalist.at(0)));
                ui->tableWidget->setItem(numds,2,new QTableWidgetItem(indatalist.at(1)));
                ui->tableWidget->setItem(numds,3,new QTableWidgetItem(indatalist.at(2)));
                ui->tableWidget->setItem(numds,4,new QTableWidgetItem(indatalist.at(3)));
                ui->tableWidget->setItem(numds,5,new QTableWidgetItem(indatalist.at(4)));
                ui->tableWidget->setItem(numds,6,new QTableWidgetItem(indatalist.at(5)));
                ui->tableWidget->setItem(numds,7,new QTableWidgetItem(indatalist.at(6)));
                ui->tableWidget->setItem(numds,8,new QTableWidgetItem(indatalist.at(7)));
                numds++;
            }
        }
    }
}
