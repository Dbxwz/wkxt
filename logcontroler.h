#ifndef LOGCONTROLER_H
#define LOGCONTROLER_H
#include <QVector>

class logControler
{
public:
    logControler();
    void stateHandle(int room, int temperature);//状态信息处理
    void windSupplyHandle(int room, int temperature, int windSpeed, int windType);//温控请求信息处理void
    void stopWindHandle(int room);//停风请求处理
    QVector<double> askEnergyAndCost(int room);//请求room用量和费用，vector第一项是用量，第二项是费用
};

#endif // LOGCONTROLER_H
