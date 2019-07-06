#include "qfinddialog.h"
#include "ui_qfinddialog.h"

QFindDialog::QFindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QFindDialog)
{
    ui->setupUi(this);
}

QFindDialog::~QFindDialog()
{
    delete ui;
}

void QFindDialog::showEvent(QShowEvent *)
{

}

void QFindDialog::on_btn_resiger_clicked()
{
    done(0);
}

void QFindDialog::setAllInfo(QStringList list)
{
    if(list.size() >= 8){
        ui->lineEdit_1->setText(list.at(0));
        ui->lineEdit_2->setText(list.at(1));
        ui->lineEdit_4->setText(list.at(2));
        ui->lineEdit_5->setText(list.at(3));
        ui->lineEdit_6->setText(list.at(4));
        ui->lineEdit_7->setText(list.at(5));
        ui->lineEdit_8->setText(list.at(6));
        ui->lineEdit_9->setText(list.at(7));
    }
}
