//****************************************
//文件名：           sold.h
//版本              1.0
//目的及主要功能      调用api
//创建日期           2020.9.10
//修改日期           2020.9.20
//作者              ctrlC
//联系方式           关注bilibili账号：肯抽C
//****************************************

#ifndef SOLD_H
#define SOLD_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
class sold : public QWidget
{
    Q_OBJECT
public:
    explicit sold(QWidget *parent = nullptr);//初始化
    QPushButton   *p_mSoldBotton;//卖按钮
    QLabel        *p_mStockInfoLabel;//股票信息按钮
    QSpinBox      *p_mNumberSoldSpinBox;//卖股票数标签
    QLabel        *p_mNumberBuyLabel;//卖股票数标签
    QLabel        *p_mPriceCurrentLabel;//当前价格
    QLabel        *p_mSumLabel;//预计总和标签
    QLabel        *p_mNumberSoldLabel;//买入股数
    QString       m_StockCode;//股票代码
    int           m_SoldNumber;//卖出股数
    float         m_CurrentPrice;//当前价格

    float         m_Sum;//总和

    void Sold_UI();//初始化界面
    void iniSignalSlots();//初始化信号
    void set_sold_info(QString,QString,QString);//设置卖出股票信息
    int get_sold_info();//获得卖出股票信息
signals:
       void signal_to_user();//回到user界面信号

public slots:
        void send_signal();//发送信号
        void sum_change();//总和改变
};

#endif // SOLD_H
