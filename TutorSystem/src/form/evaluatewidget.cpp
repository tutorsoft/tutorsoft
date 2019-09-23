#pragma execution_character_set("utf-8")
#include "evaluatewidget.h"
#include "ui_evaluatewidget.h"
#include "qxmessagebox/qxmessagebox.h"
#include "../mainwidget.h"
#include "../signalmanageobject/signalmanageobject.h"
#include <QDebug>

EvaluateWidget::EvaluateWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EvaluateWidget)
{
    ui->setupUi(this);
    MainWidget::allSignalEvent.setEvaluateWidget(this);
    pModel = new QStandardItemModel();
    icons.append(":/images/HotDog.jpg");
    icons.append(":/images/li.jpg");
    icons.append(":/images/logo.jpg");
    icons.append(":/images/PACT.jpg");
    icons.append(":/images/yang.jpg");
    icons.append(":/images/zhang.jpg");
}

EvaluateWidget::~EvaluateWidget()
{
    delete ui;
}

void EvaluateWidget::setTeacher(QString str)
{
    qDebug()<<"setTeacher";
    evaluate = "evaluate_" + str;
    QString strsend =  "EvaluateWidget_queryAll:evaluate_" + str;
    qDebug()<<"strsend--"<<strsend;
    emit sendWriteSocket(strsend);
}

void EvaluateWidget::acceptSocketData(QString ret)
{
    qDebug()<<"EvaluateWidget==>"<<ret;
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

        QString num = tlist.at(0);
        QString data =  tlist.at(1);
        QStringList datalist = data.split("*");

        for(int i = 0;i < datalist.size()-1;i++){
            QString indata = datalist.at(i);
            QStringList indatalist = indata.split("+");

            QStandardItem *pItem = new QStandardItem;
            MuItemData itemData;
            itemData.singer = indatalist.at(1);
            itemData.songsNb = indatalist.at(2);
            itemData.iconPath = icons.at(0);
            pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
            pModel->appendRow(pItem);
        }
        MuItemDelegate *pItemDelegate = new MuItemDelegate(this);
        ui->listView->setItemDelegate(pItemDelegate);
        ui->listView->setModel(pModel);
    }
}

void EvaluateWidget::on_btn_ok_clicked()
{
  QString updataStr = QString("insert into %1 values('%2','%3','%4')")
          .arg(evaluate).arg(MainWidget::currentuser).arg(MainWidget::currentusername).arg(ui->lineEdit->text());

    QString strsend =  "EvaluateWidget:" + updataStr;
    emit sendWriteSocket(strsend);

}

void EvaluateWidget::on_btn_cancel_clicked()
{
    done(0);
}
