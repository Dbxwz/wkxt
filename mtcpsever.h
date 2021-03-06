#ifndef MTCPSEVER_H
#define MTCPSEVER_H
#include <QtNetwork>
#include <QMessageBox>
#include "mtcpsocket.h"
#define MAX_CONNECT 10 //最大允许连接数

class mTcpSever:QObject
{
private:
    QTcpServer* qTcpServer;
    mTcpSocket msocket[MAX_CONNECT];

private slots:
    void SeverNewConnection();//检测到新链接的槽函数

public:
    explicit mTcpSever();
    void send2home(int home, exchangeInfo info);//给指定房间发信息
    QVector<int> getLinkedHome();//返回已经建立连接的房间号
};

#endif // MTCPSEVER_H
