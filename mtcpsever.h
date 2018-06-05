#ifndef MTCPSEVER_H
#define MTCPSEVER_H
#include <QtNetwork>
#include <QMessageBox>
#include "mtcpsocket.h"
#define MAX_CONNECT 10 //最大允许连接数

class mTcpSever
{
private:
    QTcpServer* qTcpServer;
    mTcpSocket msocket[MAX_CONNECT];

private slots:
    SeverNewConnection();//检测到新链接的槽函数

public:
    explicit mTcpSever();
};

#endif // MTCPSEVER_H
