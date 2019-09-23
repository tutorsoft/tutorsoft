﻿#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QHash>
#include "tcpsocket.h"

//继承QTCPSERVER以实现多线程TCPscoket的服务器。
//如果socket的信息处理直接处理的话，很多新建的信号和槽是用不到的
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0,int numConnections = 100);
    ~TcpServer();

    void setMaxPendingConnections(int numConnections);//重写设置最大连接数函数
signals:
    //发送新用户连接信息
    void connectClient(int,QString,int);
    //发送获得用户发过来的数据
    void readData(int socketid,quint16 size,QByteArray );
    //断开连接的用户信息
    void sockDisConnect(int ,QString ,quint16);
    //向scoket发送消息
    void sentData(const QByteArray &,const int);
    //断开特定连接，并释放资源，-1为断开所有。
    void sentDisConnect(int i);


public slots:
    QHash<int,TcpSocket *>* getHashTcpClient();
    //断开所有连接，线程计数器请0
    void clear();
protected slots:
    //断开连接的用户信息
    void sockDisConnectSlot(int handle,const QString & ip, quint16 prot, QThread *th);

protected:
    void incomingConnection(qintptr socketDescriptor);//覆盖已获取多线程
private:
    QHash<int,TcpSocket *>* tcpClient;//管理连接的map
    int maxConnections;

};


#endif // TCPSERVER_H
