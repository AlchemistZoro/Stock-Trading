//****************************************
//文件名：           user.h
//版本              1.0
//目的及主要功能      调用api
//创建日期           2020.9.10
//修改日期           2020.9.20
//作者              ctrlC
//联系方式           关注bilibili账号：肯抽C
//****************************************

#ifndef USER_H
#define USER_H
#include "sold.h"
#include "stock.h"
#include "ViewerContent.h"
#include "person.h"
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QTextBrowser>
class user : public QWidget
{
    Q_OBJECT
private:
   QPushButton     *p_mHomeButton;//返回query按钮
   QPushButton     *p_mSoldWindowBotton;//卖股票按钮

   QTextBrowser    *p_mUserInfoTextBrowser;//显示信息textbrowser
   QTableView      *p_mPositonView;//显示表格
   sold            *p_mSoldWindow;//抛售窗口
   QStandardItemModel* model;//表格数据
public:
    QPushButton     *p_mUpdateUserInfoBotton;//购买窗口
    person          *p_mperson;//人
    explicit user(QWidget *parent = nullptr);//初始化
    void User_UI();//绘制界面
    void iniSignalSlots();//连接信号与槽
    void set_info(person*);//设置人的信息
    QString output_person_info();//输出人的信息
    void sold_process(QString,int,float);//抛售过程
    void change_info();//更改信息
   void update_onestock(int,ViewerContent);//更新股票
    void calculate_currentsum();//计算总和
    QString value_change(float sum);//更改值
 signals:
    void signal_to_query();//回到主函数信号
    void signal_write();//写文件信号
public slots:
    void send_signal();//接收槽函数
    void user_to_sold();//跳转至抛售界面
    void sold_to_user();//抛售跳转user
    void update_info();//更新信息
};

#endif // USER_H
