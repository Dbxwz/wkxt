#include "exchangeinfo.h"

exchangeInfo::exchangeInfo()
{

}
exchangeInfo::exchangeInfo(QByteArray ba)
{
    QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(ba);
    this->obj = jsonDoc.object();
}

QByteArray exchangeInfo::toByte()
{
    QJsonDocument jsonDoc(this->obj);
    return jsonDoc.toJson();
}

void exchangeInfo::insertAck(bool a)
{
    this->obj.insert("Ack", QJsonValue(a));
}

bool exchangeInfo::getAck()
{
    return this->obj["Ack"].toBool();
}

void exchangeInfo::insertCost(double a)
{
    this->obj.insert("Cost", QJsonValue(a));
}

double exchangeInfo::getCost()
{
    return this->obj["Cost"].toDouble();
}

void exchangeInfo::insertEnergy(double a)
{
    this->obj.insert("Energy", QJsonValue(a));
}

double exchangeInfo::getEnergy()
{
    return this->obj["Energy"].toDouble();
}

void exchangeInfo::insertID(QString str)
{
    this->obj.insert("ID", QJsonValue(str));
}

QString exchangeInfo::getID()
{
    return this->obj["ID"].toString();
}

void exchangeInfo::insertReply(int a)
{
    this->obj.insert("Reply", QJsonValue(a));
}

int exchangeInfo::getReply()
{
    return this->obj["Reply"].toInt();
}

void exchangeInfo::insertRoom(int a)
{
    this->obj.insert("Room",QJsonValue(a));
}

int exchangeInfo::getRoom()
{
    return this->obj["Room"].toInt();
}

void exchangeInfo::insertTem(int a)
{
    this->obj.insert("Temperature",QJsonValue(a));
}

int exchangeInfo::getTem()
{
     return this->obj["Temperature"].toInt();
}

void exchangeInfo::insertType(QString str)
{
    this->obj.insert("Type", QJsonValue(str));
}

QString exchangeInfo::getType()
{
    return this->obj["Type"].toString();
}

void exchangeInfo::insertWindSpeed(int a)
{
    this->obj.insert("WindSpeed",QJsonValue(a));
}

int exchangeInfo::getWindSpeed()
{
    return this->obj["WindSpeed"].toInt();
}

void exchangeInfo::insertWindType(int a)
{
    this->obj.insert("WindType",QJsonValue(a));
}

int exchangeInfo::getWindType()
{
    return this->obj["WindType"].toInt();
}

void exchangeInfo::energyAndCost(double energy, double cost)
{
    this->obj.insert("Type","EnergyAndCost");
    insertEnergy(energy);
    insertCost(cost);
}

void exchangeInfo::replyForLogin(int reply)
{
    this->obj.insert("Type","ReplyForLogin");
    insertReply(reply);
}

void exchangeInfo::replyForState(bool ack)
{
    this->obj.insert("Type","ReplyForState");
    insertAck(ack);
}

void exchangeInfo::replyForWindSupply(bool ack)
{
    this->obj.insert("Type","ReplyForWindSupply");
    insertAck(ack);
}

void exchangeInfo::replyForStopWindSupply(bool ack)
{
    this->obj.insert("Type","ReplyForStopWindSupply");
    insertAck(ack);
}

void exchangeInfo::askWindSupply(int room, int tem, int winSpeed, int windType)
{
    this->obj.insert("Type","AskWindSupply");
    insertRoom(room);
    insertTem(tem);
    insertWindSpeed(winSpeed);
    insertWindType(windType);
}

void exchangeInfo::stopWindSupply(int room)
{
    this->obj.insert("Type","StopWindSupply");
    insertRoom(room);
}

void exchangeInfo::askLogin(int room, QString id)
{
    this->obj.insert("Type","AskLogin");
    insertRoom(room);
    insertID(id);
}

void exchangeInfo::askLogout(int room)
{
    this->obj.insert("Type","AskLogout");
    insertRoom(room);
}

void exchangeInfo::state(int room, int tem)
{
    this->obj.insert("Type","State");
    insertRoom(room);
    insertTem(tem);
}

void exchangeInfo::replyForEnergyAndCost(bool ack)
{
    this->obj.insert("Type","ReplyForEnergyAndCost");
    insertAck(ack);
}
