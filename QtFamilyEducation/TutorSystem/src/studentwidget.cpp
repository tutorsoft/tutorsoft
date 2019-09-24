#pragma execution_character_set("utf-8")
#include "studentwidget.h"
#include "ui_studentwidget.h"

StudentWidget::StudentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentWidget)
{
    ui->setupUi(this);
    m_ChildWidgetA = new ChildWidgetA(this);
    m_ChildWidgetB = new ChildWidgetB(this);
    m_ChildWidgetC = new ChildWidgetC(this);
    m_ChildWidgetD = new ChildWidgetD(this);
    m_ChildWidgetE = new ChildWidgetE(this);
    m_ChildWidgetF = new ChildWidgetF(this);

    ui->stackedWidget->addWidget(m_ChildWidgetA);
    ui->stackedWidget->addWidget(m_ChildWidgetB);
    ui->stackedWidget->addWidget(m_ChildWidgetC);
    ui->stackedWidget->addWidget(m_ChildWidgetD);
    ui->stackedWidget->addWidget(m_ChildWidgetE);
    ui->stackedWidget->addWidget(m_ChildWidgetF);

    ui->stackedWidget->setCurrentWidget(m_ChildWidgetA);
}

StudentWidget::~StudentWidget()
{
    delete ui;
}

void StudentWidget::on_btn_1_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetA);
}

void StudentWidget::on_btn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetE);
}

void StudentWidget::on_btn_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetF);
}

void StudentWidget::on_btn_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetD);
}

void StudentWidget::on_btn_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetB);
}

void StudentWidget::on_btn_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetC);
}

void StudentWidget::on_btn_quit_clicked()
{
    emit sendQuit();
}
