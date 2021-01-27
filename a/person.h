
//****************************************
//文件名：           person.h
//版本              1.0
//目的及主要功能      用户类
//创建日期           2020.9.10
//修改日期           2020.9.20
//作者              ctrlC
//联系方式           关注bilibili账号：肯抽C
//****************************************
#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include <QVector>
#include "stock.h"
class person : public QWidget
{
    Q_OBJECT
public:
    explicit person(QWidget *parent = nullptr);//初始化
    QVector<stock*> m_StockVector;//股票数组
    QString  m_Name="没钱的王先生";//用户名
    QString  m_Bank="没钱的银行";//开户券商
    float     m_current_sum;//总资产
    float     m_IniMoney=150000000;//初始资金
    float     m_BalanceMoney=150000000;//余额

signals:

public slots:
};

#endif // PERSON_H
