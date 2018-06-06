#ifndef USERCONTROLER_H
#define USERCONTROLER_H
#include <QString>

class userControler
{
public:
    userControler();
    void insertAdmin(QString name,QString psd);//插入一个admin
    bool testAdmin(QString name,QString psd);//判断一个admin是不是合法的
    void deleteAdmin(QString name);//删除一个admin
    void insertHome(int home, QString id);//插入一个房间信息
    bool testHome(int home, QString id);//判断home信息是否合法
    void deleteHome(int home);//删除对应home信息
};

#endif // USERCONTROLER_H
