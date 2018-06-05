#include "mtcpsever.h"

mTcpSever::mTcpSever()
{
    this->qTcpServer = new QTcpServer();
    if(!qTcpServer->listen(QHostAddress::Any, 6666))
    {
        QMessageBox::about(NULL,"Qt网络通信","服务器监听失败");//提示错误信息
    }
    connect(this->qTcpServer,SIGNAL(newConnection()),this,SLOT(severNewConnection()));

    for(int i = 0; i < MAX_CONNECT; i++)//socket信息的初始化
    {
       msocket[i].setIsVaild(false);
       msocket[i].setHome(-1);
    }
}

void mTcpSever::SeverNewConnection()
{
    //首先，我们要找到一个过期的socket
    int i = 0;
    for(;i < MAX_CONNECT; i++)
    {
        if(msocket[i].getIsVaild() == false)
            break;
    }

    if(i == MAX_CONNECT)
    {
        QMessageBox::about(NULL,"通信连接","连接数已满，不能再接受新连接");
        return;
    }

    msocket[i].mSocket = this->qTcpServer->nextPendingConnection();
    msocket[i].setIsVaild(true);
}
