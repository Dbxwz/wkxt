#ifndef EXCHANGEINFO_H
#define EXCHANGEINFO_H
#include <QJsonObject>
#include <QJsonDocument>

class exchangeInfo
{
private:
    QJsonObject obj;//用于封装的json对象

    void insertType(QString str);//插入type类型
    void insertEnergy(double a);//插入Energy类型
    void insertCost(double a);//插入type类型
    void insertReply(int a);//插入Reply类型
    void insertAck(bool a);//插入ack类型
    void insertRoom(int a);//插入room类型
    void insertTem(int a);//插入temperature类型
    void insertWindSpeed(int a);//插入WindSpeed类型
    void insertWindType(int a);//插入WindType类型
    void insertID(QString str);//插入ID类型
public:
    exchangeInfo();
    exchangeInfo(QByteArray ba);//将一个byte形式转化成json格式
    QByteArray toByte();//转化成byte形式
    //主机到丛机
    void energyAndCost(double energy, double cost);//用量和费用信息报文
    void replyForLogin(int reply);//登入请求恢复报文
    void replyForState(bool ack);//接受状态信息回复报文
    void replyForWindSupply(bool ack);//请求送风回复报文
    void replyForStopWindSupply(bool ack);//停止送风回复报文
    //丛机到主机
    void askWindSupply(int room, int tem, int winSpeed, int windType);//请求送风报文
    void stopWindSupply(int room);//停止送风报文
    void askLogin(int room, QString id);//登入请求报文
    void askLogout(int room);//注销请求报文
    void state(int room,int tem);//状态信息报文
    void replyForEnergyAndCost(bool ack);//用费与费用接受回复报文
    //获取信息
    QString getType();//得到type类型
    double getEnergy();//得到Energy类型
    double getCost();//得到type类型
    int getReply();//得到Reply类型
    bool getAck();//得到ack类型
    int getRoom();//得到room类型
    int getTem();//得到temperature类型
    int getWindSpeed();//得到WindSpeed类型
    int getWindType();//得到WindType类型
    QString getID();//得到ID类型
};

#endif // EXCHANGEINFO_H
