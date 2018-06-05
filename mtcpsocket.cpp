#include "mtcpsocket.h"

mTcpSocket::mTcpSocket()
{
    //this->mSocket = new QTcpSocket(prem);
    connect(this->mSocket,SIGNAL(readyRead()),this,SLOT(severReadDate()));
    connect(this,SIGNAL(wait_for_ack(exchangeInfo)),this,SLOT(waitAck(exchangeInfo)));
}

void mTcpSocket::run()
{

}

void mTcpSocket::severReadDate()
 {
    getInfo = this->mSocket->readAll();

     if(getInfo.isEmpty())
     {
        return;//接受的空串，不做处理（也可以做消息提示）
     }


     exchangeInfo obj(getInfo);
     QString type = obj.getType();
     if(type.compare("AskWindSupply"))
     {
         //调用报表函数处理
         exchangeInfo reply;
         reply.replyForWindSupply(true);
         this->mSocket->write(reply.toByte());
     } else if(type.compare("StopWindSupply"))
     {
         //.....
         exchangeInfo reply;
         reply.replyForStopWindSupply(true);
         this->mSocket->write(reply.toByte());
     } else if(type.compare("AskLogin"))
     {
         exchangeInfo reply;
         if(true)//此处需要接口
         {
             reply.replyForLogin(true);
             this->setHome(obj.getRoom());
         }
         else
         {
             reply.replyForLogin(false);
         }
         this->mSocket->write(reply.toByte());
     } else if(type.compare("AskLogout"))
     {
         socketClose();
         emit this->socket_disconnect();
     } else if(type.compare("State"))
     {
         //..
         exchangeInfo reply;
         reply.replyForState(true);
         this->mSocket->write(reply.toByte());
     } else if(type.compare("ReplyForEnergyAndCost"))
     {
     }

 }

void mTcpSocket::severWriteDate()
 {
     this->mSocket->write(this->sendInfo.toByte());
     if(sendInfo.getType() == "EnergyAndCost")
     {
        emit wait_for_ack(this->sendInfo);
     }
 }

void mTcpSocket::waitAck(exchangeInfo info)
 {
     QTime startTime = QTime::currentTime();
     while(true)
     {
         exchangeInfo obj(getInfo);
         if(obj.getType() == "ReplyForEnergyAndCost")
             break;
         QTime endtime = QTime::currentTime();
         if(endtime.msecsTo(startTime) % 50 == 0)//50ms重传一次
            this->mSocket->write(info.toByte());//超时重传
     }
 }

void mTcpSocket::socketClose()
{
    this->setIsVaild(false);
    this->setHome(-1);
    this->mSocket->close();
}

void mTcpSocket::onDisconnect()
{
    this->setIsVaild(false);
    emit socket_disconnect();//发送一个断开连接SIGNAL
}

void mTcpSocket::setHome(int a)
{
    this->home = a;
}

void mTcpSocket::setIsVaild(bool a)
{
    this->isVaild = a;
}

int mTcpSocket::getHome()
{
    return this->home;
}

bool mTcpSocket::getIsVaild()
{
    return this->isVaild;
}
