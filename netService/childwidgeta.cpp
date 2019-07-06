#pragma execution_character_set("utf-8")
#include "registerstudentwidget.h"
#include "childwidgeta.h"
#include "ui_childwidgeta.h"
#include "userdatabase.h"
#include "qxmessagebox.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"

ChildWidgetA::ChildWidgetA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetA)
{
    ui->setupUi(this);

    selectrow = -1;
    QStringList header;
    header << "学生编号" <<"密码"<< "学生姓名"<<"性别"<<"年龄"<<"电话"<<"邮箱"<<"年级";
    ui->tableWidget->setColumnCount(8);
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
    ui->tableWidget->horizontalHeader()->resizeSection(6,ui->tableWidget->width()*0.2);
    ui->tableWidget->horizontalHeader()->resizeSection(7,ui->tableWidget->width()*0.2);
    ui->tableWidget->horizontalHeader()->setStyleSheet(TAB_WIDGET_STYLE);

    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);
    updateDisplay();

    connect(ui->tableWidget, SIGNAL(cellClicked(int , int )),
            this, SLOT(onHeaderClicked(int,int)));
}

ChildWidgetA::~ChildWidgetA()
{
    delete ui;
}

void ChildWidgetA::on_btn_add_clicked()
{
    RegisterStudentWidget w;
    w.exec();
}

void ChildWidgetA::on_btn_del_clicked()
{
    if(selectrow >= 0 ){
    QString id = ui->tableWidget->item(selectrow,0)->text();
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }
    QSqlQuery query(userDataBasePri::database);


    QString statement = QString("delete from student_information where studentid = '%1'").arg(id);
    query.exec(statement);
    qDebug()<<"asdf"<<query.lastError()<<statement;
    userDataBasePri::database.close();
    updateDisplay();
    }
}

void ChildWidgetA::showEvent(QShowEvent *event)
{
    updateDisplay();
}

void ChildWidgetA::updateDisplay()
{
    QString tstr0 = "student_information" ;

    ui->tableWidget->clearContents();
    QVector<QVector<QString>>  allinfo = queryAll(tstr0);
    qDebug()<<"updateDisplay"<<allinfo.size();
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
    }
}

QVector<QVector<QString> > ChildWidgetA::queryAll(QString tablename)
{
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }
    QSqlQuery query(userDataBasePri::database);
    QString statement = QString("SELECT * FROM %1").arg(tablename);
    query.exec(statement);
    qDebug()<<"teacher_information"<<query.lastError();
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

void ChildWidgetA::onHeaderClicked(int row,int column)
{
    selectrow = row;


}
