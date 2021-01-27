//****************************************
//文件名：           query.h
//版本              1.0
//目的及主要功能      查询界面/主界面
//创建日期           2020.9.10
//修改日期           2020.9.20
//作者              ctrlC
//联系方式           关注bilibili账号：肯抽C
//****************************************
#ifndef QUERY_H
#define QUERY_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextBrowser>
#include <QPixmap>

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

#include "user.h"
#include "buy.h"
#include "person.h"
#include "ViewerContent.h"
class Query : public QDialog
{
    Q_OBJECT
private:
    person          *p_mperson;//用户对象指针
    QPushButton     *p_mToQueryButton;//查询按钮指针
    QPushButton     *p_mBuyButton;//购买指针
    QPushButton     *p_mUserButton;//用户按钮指针
    QLineEdit       *p_mQueryLineEdit;//查询指针
    QLabel          *p_mKPictureLabel;//k线图片
    QLabel          *p_mDPictureLabel;//D线图片
    QTextBrowser    *p_mStockIfoTextBrowser;//信息界面
    user            *p_mUserWindow;//用户窗口指针
    buy             *p_mBuyWindow;//购买窗口指针
    QString         m_code;//股票代码
    QString         m_price;//股票价格
    ViewerContent   m_vct;//content对象
    void Query_UI();//初始化ui
    void iniSignalSlots();//连接槽函数
   QString output_person_info();//人的信息

public slots:
    void start_write_json();//开始写文件
    void query_to_user();//查询前往用户
    void user_to_query();//用户前往查询
    void query_to_buy();//查询前往购买
    void buy_to_query();//购买前往查询
    void slot_update();//更新槽函数
    void buy_stock(int);//买股票
signals:

public:
    Query(QWidget *parent = 0);//初始化
    ~Query();
    void updateViewer(ViewerContent vct);//创建cotent类
    void json_read();//读json
    void json_write();//写json
    void calculate_currentsum();//计算总价
    QString  value_change(float);//更改值的表达方式

};

#endif // QUERY_H
