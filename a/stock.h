//****************************************
//文件名：           stock.h
//版本              1.0
//目的及主要功能      调用api
//创建日期           2020.9.10
//修改日期           2020.9.20
//作者              ctrlC
//联系方式           关注bilibili账号：肯抽C
//****************************************
#ifndef STOCK_H
#define STOCK_H

#include <QObject>
#include<Qstring>
#include<QPixmap>
class stock : public QObject
{
    Q_OBJECT
public:
    explicit stock(QObject *parent = nullptr);//初始化
    QString get_stockCode(){return m_stockCode;}//获得股票代码
    QString get_stockName(){return m_stockName;}//获得股票名
    QString get_time(){return m_time;}//获得当前时间
    QString get_date(){return m_date;}//获得日期
    QString get_openingPrice(){return m_openingPrice;}//获得开盘价
    QString get_current(){return m_current;}//获得当前价
    QString get_turnover(){return m_turnover;}//获得收盘价
    QString get_min(){return m_min;}//获得最低价
    QString get_max(){return m_max;}//获得最高价
    QPixmap get_timeLinePixmap(){return m_timeLinePixmap;}//获得D线图
    QPixmap get_dayKLinePixmap(){return m_dayKLinePixmap;}//获得K线图

    void set_stockCode(QString stockcode){m_stockCode=stockcode;}//设置股票代码
    void set_stockName(QString stockName){m_stockName=stockName;}//设置股票名
    void set_time(QString time){m_time=time;}//设置时间
    void set_date(QString date){m_date=date;}//设置日期
    void set_openingPrice(QString openingPrice){m_openingPrice=openingPrice;}//设置开盘价
    void set_current(QString current){m_current=current;}//设置当前价
    void set_turnover(QString turnover){m_turnover=turnover;}//设置收盘价
    void set_min(QString min){m_min=min;}//设置最低价
    void set_max(QString max){m_max=max;}//设置最高价
    void set_timeLinePixmap(QPixmap timeLinePixmap){m_timeLinePixmap=timeLinePixmap;}//设置D线图
    void set_dayKLinePixmap(QPixmap dayKLinePixmap){m_dayKLinePixmap=dayKLinePixmap;}//设置K线图


    int m_stockNumber=0;//购买股票数
    float m_stockPrice=0;//当前股票价
private:
    //QString m_Info;
    QString m_stockCode;//股票代码
    QString m_stockName;//股票名
    QString m_time;//时间
    QString m_date;//日期

    QString m_openingPrice;//开盘价
    QString m_current;//当前价
    //QString m_amount;//
    QString m_turnover;//收盘价
    QString m_min;//最小值
    QString m_max;//最大值



    QPixmap m_timeLinePixmap;//D 线图
    QPixmap m_dayKLinePixmap;//k线图

};

#endif // STOCK_H
