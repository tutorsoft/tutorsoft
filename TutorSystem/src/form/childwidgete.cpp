#pragma execution_character_set("utf-8")
#include "childwidgete.h"
#include "ui_childwidgete.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../database/userdatabase.h"
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

ChildWidgetE::~ChildWidgetE()
{
    delete ui;
}

void ChildWidgetE::showEvent(QShowEvent *event)
{
    updateDisplay();
}

void ChildWidgetE::updateDisplay()
{
    ui->tableWidget->clearContents();
    QVector<QVector<QString>>  allinfo = queryAll("teacher_information");
    int num = 0;
    for(int i = 0;i < allinfo.size();i++){
        if(allinfo.at(i).at(7) == "初中"){
            num++;
        }
    }

    ui->tableWidget->setRowCount(num);
    num = 0;
    for(int i = 0;i < allinfo.size();i++){
        if(allinfo.at(i).at(7) == "初中"){
            ui->tableWidget->setItem(num,0,new QTableWidgetItem(allinfo.at(i).at(0)));
            ui->tableWidget->setItem(num,1,new QTableWidgetItem(allinfo.at(i).at(2)));
            ui->tableWidget->setItem(num++,2,new QTableWidgetItem(allinfo.at(i).at(7)));
        }
    }
}

QVector<QVector<QString> > ChildWidgetE::queryAll(QString tablename)
{
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }
    QSqlQuery query(userDataBasePri::database);
    QString statement = QString("SELECT * FROM %1").arg(tablename);
    query.exec(statement);
    QVector<QVector<QString>> retvector;
    QVector<QString> vectorstr;
    int midsize = 0;
    while(query.next())
    {
        vectorstr.clear();
        midsize = query.size();
        for(int i = 0; i < 40;i++ ){
            vectorstr.append(query.value(i).toByteArray());
        }
        retvector.append(vectorstr);
    }
    userDataBasePri::database.close();
    return retvector;
}

void ChildWidgetE::onHeaderClicked(int row,int column)
{
    selectrow = row;

}


void ChildWidgetE::on_btn_find_clicked()
{

}

void ChildWidgetE::on_btn_look_clicked()
{

}
