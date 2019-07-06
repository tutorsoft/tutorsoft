#pragma execution_character_set("utf-8")
#include "tcpsocket.h"
#include <QtConcurrent/QtConcurrent>
#include <QHostAddress>
#include <QDebug>
#include "userdatabase.h"
TcpSocket::TcpSocket(qintptr socketDescriptor, QObject *parent) : //构造函数在主线程执行，lambda在子线程
    QTcpSocket(parent),socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);
    connect(this,&TcpSocket::readyRead,this,&TcpSocket::readData);
    dis = connect(this,&TcpSocket::disconnected,
                  [&](){
        qDebug() << "disconnect" ;
        emit sockDisConnect(socketID,this->peerAddress().toString(),this->peerPort(),QThread::currentThread());//发送断开连接的用户信息
        this->deleteLater();
    });
    connect(&watcher,&QFutureWatcher<QByteArray>::finished,this,&TcpSocket::startNext);
    connect(&watcher,&QFutureWatcher<QByteArray>::canceled,this,&TcpSocket::startNext);
    qDebug() << "new connect" ;
}

TcpSocket::~TcpSocket()
{
}


void TcpSocket::sentData(const QByteArray &data, const int id)
{
    if(id == socketID)
    {
        write(data);
    }
}

void TcpSocket::disConTcp(int i)
{
    if (i == socketID)
    {
        this->disconnectFromHost();
    }
    else if (i == -1) //-1为全部断开
    {
        disconnect(dis); //先断开连接的信号槽，防止二次析构
        this->disconnectFromHost();
        this->deleteLater();
    }
}

void TcpSocket::readData()
{
    QByteArray buff = this->readAll();
    emit sendData(socketID,buff.size(),buff);
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }

    QSqlQuery query(userDataBasePri::database);
    QString t_str(buff);
    qDebug()<<"readData-->"<<t_str;
    QStringList t_strlist = t_str.split(":");
    QString t_flog = t_strlist.at(0);
    if(t_flog == "login"){
        QString password = t_strlist.at(2);
        QString querystr = t_strlist.at(1);
        query.exec(querystr);
        QString t_password;
        QString t_root;
        while (query.next()){
            t_password = query.value(1).toString();
            t_root = query.value(2).toString();
        }
        if(password == t_password){
            qDebug()<<"登录成功"<<password;
            qDebug()<<"登录成功"<<t_password;
            QString retstr = "login:true";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "login:false";
            this->write(retstr.toStdString().c_str());
            qDebug()<<"登录失败"<<password;
            qDebug()<<"登录失败"<<t_password;
        }

    }else if(t_flog == "RegisterStudent"){
        QString querystr = t_strlist.at(1);

        bool ret = query.exec(querystr);
        if(ret == false){
            QString retstr = "RegisterStudent:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "RegisterStudent:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "RegisterTeacher"){
        QString querystr = t_strlist.at(1);
        bool ret = query.exec(querystr);
        if(ret == false){
            qDebug()<<"query"<<query.lastError();
            QString retstr = "RegisterTeacher:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "RegisterTeacher:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetA"){
        QString querystr = t_strlist.at(1);
        bool ret = query.exec(querystr);
        if(ret == false){
            qDebug()<<"query"<<query.lastError();
            QString retstr = "ChildWidgetA:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "ChildWidgetA:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetB"){
        QString querystr = t_strlist.at(1);
        bool ret = query.exec(querystr);
        if(ret == false){
            qDebug()<<"query"<<query.lastError();
            QString retstr = "ChildWidgetB:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "ChildWidgetB:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetC"){
        QString querystr = t_strlist.at(1);
        bool ret = query.exec(querystr);
        if(ret == false){
            qDebug()<<"query"<<query.lastError();
            QString retstr = "ChildWidgetC:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "ChildWidgetC:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetG"){
        QString querystr = t_strlist.at(1);
        bool ret = query.exec(querystr);
        if(ret == false){
            qDebug()<<"query"<<query.lastError();
            QString retstr = "ChildWidgetG:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "ChildWidgetG:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetH"){

        QString querystr = t_strlist.at(1);
        qDebug()<<"ChildWidgetH---**>"<<querystr;
        bool ret = query.exec(querystr);
        if(ret == false){
            qDebug()<<"query"<<query.lastError();
            QString retstr = "ChildWidgetH:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "ChildWidgetH:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetI"){
        QString querystr = t_strlist.at(1);
        bool ret = query.exec(querystr);
        if(ret == false){
            qDebug()<<"query"<<query.lastError();
            QString retstr = "ChildWidgetI:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "ChildWidgetI:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetJ"){
        QString querystr = t_strlist.at(1);
        bool ret = query.exec(querystr);
        if(ret == false){
            qDebug()<<"query"<<query.lastError();
            QString retstr = "ChildWidgetJ:false";
            this->write(retstr.toStdString().c_str());
        }else{
            QString retstr = "ChildWidgetJ:true";
            this->write(retstr.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetA_queryAll"){
        QString tablename = t_strlist.at(1);
        QString currentuser = t_strlist.at(2);
        QString querystr = QString("SELECT * FROM %1").arg(tablename);
        bool ret = query.exec(querystr);
        QString retstr;
        if(ret == true){
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

            for(int i =0;i < retvector.size();i++){
                if(currentuser == retvector.at(i).at(0)){
                    retstr.append(retvector.at(i).at(0));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(1));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(2));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(3));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(4));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(5));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(6));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(7));
                }
            }
        }

        QString retstrs;
        retstrs.append("ChildWidgetA_queryAll:");
        retstrs.append(retstr);
        qDebug()<<"retstrs==="<<retstrs;
        this->write(retstrs.toStdString().c_str());
    }else if(t_flog == "ChildWidgetC_queryAll"){
        QString tablename = t_strlist.at(1);
        qDebug()<<"tablename"<<tablename;
        QString querystr = QString("SELECT * FROM %1").arg(tablename);
        bool ret = query.exec(querystr);
        if(ret == true){
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
            QString retstr;
            for(int i =0;i < retvector.size();i++){
                retstr.append(retvector.at(i).at(0));
                retstr.append("+");
                retstr.append(retvector.at(i).at(1));
                retstr.append("+");
                retstr.append(retvector.at(i).at(2));
                retstr.append("+");
                retstr.append(retvector.at(i).at(3));
                retstr.append("+");
                retstr.append(retvector.at(i).at(4));
                retstr.append("+");
                retstr.append(retvector.at(i).at(5));
                retstr.append("+");
                retstr.append(retvector.at(i).at(6));
                retstr.append("+");
                retstr.append(retvector.at(i).at(7));
                retstr.append("+");
                retstr.append(retvector.at(i).at(8));
                retstr.append("+");
                retstr.append(retvector.at(i).at(9));
                retstr.append("*");
            }
            QString retstrs;
            qDebug()<<"retvector.size()=="<<retvector.size();
            retstrs.append("ChildWidgetC_queryAll:");
            retstrs.append(QString::number(retvector.size()));
            retstrs.append(":");
            retstrs.append(retstr);
            qDebug()<<"asdfasdf"<<retstrs;
            this->write(retstrs.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetG_queryAll"){
        QString tablename = t_strlist.at(1);
        QString currentuser = t_strlist.at(2);
        QString querystr = QString("SELECT * FROM %1").arg(tablename);
        bool ret = query.exec(querystr);
        QString retstr;
        if(ret == true){
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

            for(int i =0;i < retvector.size();i++){
                if(currentuser == retvector.at(i).at(0)){
                    retstr.append(retvector.at(i).at(0));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(1));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(2));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(3));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(4));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(5));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(6));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(7));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(8));
                }
            }
        }

        QString retstrs;
        retstrs.append("ChildWidgetG_queryAll:");
        retstrs.append(retstr);
        qDebug()<<"retstrs==="<<retstrs;
        this->write(retstrs.toStdString().c_str());
    }else if(t_flog == "ChildWidgetD_queryAll"){
        QString tablename = t_strlist.at(1);
        qDebug()<<"tablename"<<tablename;
        QString querystr = QString("SELECT * FROM %1").arg(tablename);
        bool ret = query.exec(querystr);
        if(ret == true){
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
            QString retstr;
            for(int i =0;i < retvector.size();i++){
                retstr.append(retvector.at(i).at(0));
                retstr.append("+");
                retstr.append(retvector.at(i).at(1));
                retstr.append("+");
                retstr.append(retvector.at(i).at(2));
                retstr.append("+");
                retstr.append(retvector.at(i).at(3));
                retstr.append("+");
                retstr.append(retvector.at(i).at(4));
                retstr.append("+");
                retstr.append(retvector.at(i).at(5));
                retstr.append("+");
                retstr.append(retvector.at(i).at(6));
                retstr.append("+");
                retstr.append(retvector.at(i).at(7));
                retstr.append("+");
                retstr.append(retvector.at(i).at(8));
                retstr.append("*");
            }
            QString retstrs;
            qDebug()<<"retvector.size()=="<<retvector.size();
            retstrs.append("ChildWidgetD_queryAll:");
            retstrs.append(QString::number(retvector.size()));
            retstrs.append(":");
            retstrs.append(retstr);
            qDebug()<<"asdfasdf"<<retstrs;
            this->write(retstrs.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetE_queryAll"){
        QString tablename = t_strlist.at(1);
        qDebug()<<"tablename"<<tablename;
        QString querystr = QString("SELECT * FROM %1").arg(tablename);
        bool ret = query.exec(querystr);
        if(ret == true){
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
            QString retstr;
            for(int i =0;i < retvector.size();i++){
                retstr.append(retvector.at(i).at(0));
                retstr.append("+");
                retstr.append(retvector.at(i).at(1));
                retstr.append("+");
                retstr.append(retvector.at(i).at(2));
                retstr.append("+");
                retstr.append(retvector.at(i).at(3));
                retstr.append("+");
                retstr.append(retvector.at(i).at(4));
                retstr.append("+");
                retstr.append(retvector.at(i).at(5));
                retstr.append("+");
                retstr.append(retvector.at(i).at(6));
                retstr.append("+");
                retstr.append(retvector.at(i).at(7));
                retstr.append("+");
                retstr.append(retvector.at(i).at(8));
                retstr.append("*");
            }
            QString retstrs;
            qDebug()<<"retvector.size()=="<<retvector.size();
            retstrs.append("ChildWidgetE_queryAll:");
            retstrs.append(QString::number(retvector.size()));
            retstrs.append(":");
            retstrs.append(retstr);
            qDebug()<<"asdfasdf"<<retstrs;
            this->write(retstrs.toStdString().c_str());
        }
    }else if(t_flog == "ChildWidgetF_queryAll"){
        QString tablename = t_strlist.at(1);
        qDebug()<<"tablename"<<tablename;
        QString querystr = QString("SELECT * FROM %1").arg(tablename);
        bool ret = query.exec(querystr);
        if(ret == true){
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
            QString retstr;
            for(int i =0;i < retvector.size();i++){
                retstr.append(retvector.at(i).at(0));
                retstr.append("+");
                retstr.append(retvector.at(i).at(1));
                retstr.append("+");
                retstr.append(retvector.at(i).at(2));
                retstr.append("+");
                retstr.append(retvector.at(i).at(3));
                retstr.append("+");
                retstr.append(retvector.at(i).at(4));
                retstr.append("+");
                retstr.append(retvector.at(i).at(5));
                retstr.append("+");
                retstr.append(retvector.at(i).at(6));
                retstr.append("+");
                retstr.append(retvector.at(i).at(7));
                retstr.append("+");
                retstr.append(retvector.at(i).at(8));
                retstr.append("*");
            }
            QString retstrs;
            qDebug()<<"retvector.size()=="<<retvector.size();
            retstrs.append("ChildWidgetF_queryAll:");
            retstrs.append(QString::number(retvector.size()));
            retstrs.append(":");
            retstrs.append(retstr);
            qDebug()<<"asdfasdf"<<retstrs;
            this->write(retstrs.toStdString().c_str());
        }
    }
    else if(t_flog == "ChildWidgetH_queryAll"){
            QString tablename = t_strlist.at(1);
            qDebug()<<"tablename"<<tablename;
            QString querystr = QString("SELECT * FROM %1").arg(tablename);
            bool ret = query.exec(querystr);
            if(ret == true){
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
                QString retstr;
                for(int i =0;i < retvector.size();i++){
                    retstr.append(retvector.at(i).at(0));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(1));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(2));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(3));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(4));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(5));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(6));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(7));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(8));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(9));
                    retstr.append("*");
                }
                QString retstrs;
                qDebug()<<"retvector.size()=="<<retvector.size();
                retstrs.append("ChildWidgetH_queryAll:");
                retstrs.append(QString::number(retvector.size()));
                retstrs.append(":");
                retstrs.append(retstr);
                qDebug()<<"asdfasdf"<<retstrs;
                this->write(retstrs.toStdString().c_str());
            }
        }
    else if(t_flog == "ChildWidgetI_queryAll"){
            QString tablename = t_strlist.at(1);
            qDebug()<<"tablename"<<tablename;
            QString querystr = QString("SELECT * FROM %1").arg(tablename);
            bool ret = query.exec(querystr);
            if(ret == true){
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
                QString retstr;
                for(int i =0;i < retvector.size();i++){
                    retstr.append(retvector.at(i).at(0));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(1));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(2));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(3));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(4));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(5));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(6));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(7));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(8));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(9));
                    retstr.append("*");
                }
                QString retstrs;
                qDebug()<<"retvector.size()=="<<retvector.size();
                retstrs.append("ChildWidgetI_queryAll:");
                retstrs.append(QString::number(retvector.size()));
                retstrs.append(":");
                retstrs.append(retstr);
                qDebug()<<"asdfasdf"<<retstrs;
                this->write(retstrs.toStdString().c_str());
            }
        }
    else if(t_flog == "ChildWidgetJ_queryAll"){
            QString tablename = t_strlist.at(1);
            qDebug()<<"tablename"<<tablename;
            QString querystr = QString("SELECT * FROM %1").arg(tablename);
            bool ret = query.exec(querystr);
            if(ret == true){
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
                QString retstr;
                for(int i =0;i < retvector.size();i++){
                    retstr.append(retvector.at(i).at(0));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(1));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(2));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(3));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(4));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(5));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(6));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(7));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(8));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(9));
                    retstr.append("*");
                }
                QString retstrs;
                qDebug()<<"retvector.size()=="<<retvector.size();
                retstrs.append("ChildWidgetJ_queryAll:");
                retstrs.append(QString::number(retvector.size()));
                retstrs.append(":");
                retstrs.append(retstr);
                qDebug()<<"asdfasdf"<<retstrs;
                this->write(retstrs.toStdString().c_str());
            }
        }
    else if(t_flog == "ChildWidgetK_queryAll"){
            QString tablename = t_strlist.at(1);
            qDebug()<<"tablename"<<tablename;
            QString querystr = QString("SELECT * FROM %1").arg(tablename);
            bool ret = query.exec(querystr);
            if(ret == true){
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
                QString retstr;
                for(int i =0;i < retvector.size();i++){
                    retstr.append(retvector.at(i).at(0));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(1));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(2));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(3));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(4));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(5));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(6));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(7));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(8));
                    retstr.append("+");
                    retstr.append(retvector.at(i).at(9));
                    retstr.append("*");
                }
                QString retstrs;
                qDebug()<<"retvector.size()=="<<retvector.size();
                retstrs.append("ChildWidgetK_queryAll:");
                retstrs.append(QString::number(retvector.size()));
                retstrs.append(":");
                retstrs.append(retstr);
                qDebug()<<"asdfasdf"<<retstrs;
                this->write(retstrs.toStdString().c_str());
            }
        }




}
void TcpSocket::startNext()
{
    this->write(watcher.future().result());
    if (!datas.isEmpty())
    {
        //watcher.setFuture(QtConcurrent::run(this,&TcpSocket::handleData,datas.dequeue(),this->peerAddress().toString(),this->peerPort()));
    }
}
