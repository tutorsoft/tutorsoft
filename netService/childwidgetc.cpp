#pragma execution_character_set("utf-8")
#include "childwidgetc.h"
#include "ui_childwidgetc.h"
#include "userdatabase.h"
#include "qxmessagebox.h"
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

void ChildWidgetC::on_btn_add_clicked()
{

}

void ChildWidgetC::on_btn_del_clicked()
{

}

void ChildWidgetC::showEvent(QShowEvent *event)
{
    updateDisplay();
}

void ChildWidgetC::updateDisplay()
{
    QString tstr0;
    ui->tableWidget->clearContents();
    QVector<QVector<QString>>  allinfo = queryAll(tstr0);
    ui->tableWidget->setRowCount(allinfo.size());
    for(int i =0;i < allinfo.size();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(allinfo.at(i).at(0)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(allinfo.at(i).at(1)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(allinfo.at(i).at(2)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(allinfo.at(i).at(3)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(allinfo.at(i).at(4)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(allinfo.at(i).at(5)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(allinfo.at(i).at(6)));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(allinfo.at(i).at(7)));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(allinfo.at(i).at(8)));
    }
}

QVector<QVector<QString> > ChildWidgetC::queryAll(QString tablename)
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

void ChildWidgetC::onHeaderClicked(int row,int column)
{
    selectrow = row;


}
