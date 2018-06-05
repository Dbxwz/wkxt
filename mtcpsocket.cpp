#include "mtcpsocket.h"

mTcpSocket::mTcpSocket()
{
    //this->mSocket = new QTcpSocket(prem);
    connect(this->mSocket,SIGNAL(readyRead()),this,SLOT(severReadDate()));
    connect(this,SIGNAL(wait_for_ack(exchangeInfo)),this,SLOT(waitAck(exchangeInfo)));
}

void mTcpSocket::severReadDate()
 {
    this->mSocket->read(getInfo);

     if(getInfo.isEmpty())
     {
        return;//接受的空串，不做处理（也可以做消息提示）
     }


     exchangeInfo obj = new exchangeInfo(getInfo);
     QString type = obj.getType();
     switch (type) {
     case "AskWindSupply":
         //调用报表函数处理
         exchangeInfo reply = new exchangeInfo();
         reply.replyForWindSupply(true);
         this->mSocket->write(reply.toByte());
         break;
     case "StopWindSupply":
         //.....
         exchangeInfo reply = new exchangeInfo();
         reply.replyForStopWindSupply(true);
         this->mSocket->write(reply.toByte());
         break;
     case "AskLogin":
         exchangeInfo reply = new exchangeInfo();
         if()//此处需要接口
         {
             reply.replyForLogin(true);
             this->setHome(obj.getRoom());
         }
         else
         {
             reply.replyForLogin(false);
         }
         this->mSocket->write(reply.toByte());
         break;
     case "AskLogout":
         socketClose();
         socket_disconnect();
         break;
     case "State":
         //..
         exchangeInfo reply = new exchangeInfo();
         reply.replyForState(true);
         this->mSocket->write(reply.toByte());
         break;
     case "ReplyForEnergyAndCost":

         break;
     default:
         break;
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
         exchangeInfo obj = new exchangeInfo(getInfo);
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
    socket_disconnect();//发送一个断开连接SIGNAL
}
