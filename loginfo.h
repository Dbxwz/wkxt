#ifndef LOGINFO_H
#define LOGINFO_H


class logInfo
{
private:
    int id;//log的id
    int home;//房间号
    bool state;//房间开关机状态，通过状态变化判断开关机次数
    QString startTime;//起始时间
    QString endTime;//结束时间
    int startTem;//起始温度
    int endTem;//结束温度
    double cost;//费用

public:
    logInfo();
};

#endif // LOGINFO_H
