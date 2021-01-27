//****************************************
//文件名：           buy.h
//版本              1.0
//目的及主要功能      购买操作
//创建日期           2020.9.10
//修改日期           2020.9.20
//作者              ctrlC
//联系方式           关注bilibili账号：肯抽C
//****************************************

#ifndef BUY_H
#define BUY_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QString>
class buy : public QWidget
{
    Q_OBJECT
public:
    explicit buy(QWidget *parent = nullptr);
    QString          m_code1;//购买股票代码
    QString          m_price1;//单价
    void set_code(QString);//设置股票代码
    void set_price(QString);//设置单价
    void set_sum();//设置总价
    void set_balance(float );//设置余额
    void Buy_UI();//绘制界面
    void iniSignalSlots();//初始化槽函数
  int send_stockbuy_number();//发送购买股票数
   QLabel          *p_mStockNumberLabel;//股票数label
   QLabel          *p_mStockCodeLabel;//股票代码label
   QLabel          *p_mCurrentPriceLabel;//当前价格label
   QSpinBox        *p_mStockNumberSPinBox;//购买数spinbox
   QLabel          *p_mSumLabel;//总和label
   QLabel          *p_mBalanceLabel;//余额label
   QPushButton     *p_mConfirmBuyButton;//确认购买label
   int              m_MaxBuyNumber;//最大购买数
   int              m_userbalance;//当前余额数

signals:
    void signal_to_query();//回到主界面信号
public slots:
    void send_signal();//发送信号槽函数
    void sum_change();//总价更改槽函数

    
};

#endif // BUY_H
