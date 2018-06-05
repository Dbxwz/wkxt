#ifndef MTCPSOCKET_H
#define MTCPSOCKET_H
#include <QtNetwork>
#include <QThread>
#include "exchangeInfo.h"

class mTcpSocket:public QThread
{
private:
    bool isVaild;//判断当前套接字是否有效
    int home;//当前线程绑定的房间号

public:
    mTcpSocket();//将传入的socket
    QTcpSocket* mSocket;//套接字，初始化类时传入：也就是每个线程有一个socket
    QByteArray getInfo;//得到信息的缓存
    exchangeInfo sendInfo;//发送信息的缓存
    void socketClose();//关闭连接
    void setIsVaild(bool a);
    bool getIsVaild();
    void setHome(int a);
    int getHome();

private slots:
    void severReadDate();//接收数据
    void severWriteDate();//发送数据,信号连接
    void waitAck(exchangeInfo info);//等待ack
    void onDisconnect();//断线处理

signals:
    void wait_for_ack(exchangeInfo info);
    void socket_disconnect();

protected:
    void run();//重写run函数,内部进行逻辑分析
};

#endif // MTCPSOCKET_H
