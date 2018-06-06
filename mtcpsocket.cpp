#include "mtcpsocket.h"
#include "usercontroler.h"
#include "logcontroler.h"

#define SEND_TIME 50
#define TIME_OUT_TTL 50

mTcpSocket::mTcpSocket()
{
    //this->mSocket = new QTcpSocket(prem);
    connect(this->mSocket,SIGNAL(readyRead()),this,SLOT(severReadDate()));
    connect(this,SIGNAL(wait_for_ack(exchangeInfo)),this,SLOT(waitAck(exchangeInfo)));
}

void mTcpSocket::run()
{
    QTime startTime = QTime::currentTime();
    while(true)
    {
        exchangeInfo obj();
        QVector<double> vec = logControler::askEnergyAndCost(this->getHome());
        obj.energyAndCost(vec[0],vec[1]);
        QTime endtime = QTime::currentTime();
        if(endtime.msecsTo(startTime) % SEND_TIME == 0)//50ms重传一次
           this->mSocket->write(info.toByte());//超时重传
    }
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
         logControler::windSupplyHandle(obj.getRoom(),obj.getTem(),obj.getWindSpeed(),obj.getWindType());
         exchangeInfo reply;
         reply.replyForWindSupply(true);
         this->mSocket->write(reply.toByte());
     } else if(type.compare("StopWindSupply"))
     {
         logControler::stopWindHandle(obj.getRoom());
         exchangeInfo reply;
         reply.replyForStopWindSupply(true);
         this->mSocket->write(reply.toByte());
     } else if(type.compare("AskLogin"))
     {
         exchangeInfo reply;
         if(userControler::testHome(obj.getRoom(),obj.getID())//此处需要接口
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
         logControler::stateHandle(obj.getRoom(),obj.getTem());
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
         if(endtime.msecsTo(startTime) % TIME_OUT_TTL == 0)//50ms重传一次
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
