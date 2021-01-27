#include "buy.h"
#include "query.h"
#include "ViewerContent.h"
#include    <QHBoxLayout>
#include    <QVBoxLayout>
#include    <QDebug>
# include   <QMessageBox>
//**********************************
//name:buy
//
//input:QWidget *parent
//
//output:void
//
//description:更新槽函数
//**********************************
buy::buy(QWidget *parent) : QWidget(parent)
{

    Buy_UI();
    iniSignalSlots();

}
//**********************************
//name:iniSignalSlots()
//
//input:void
//
//output:void
//
//description:更新槽函数
//**********************************
void buy::iniSignalSlots()
{
    connect(p_mConfirmBuyButton,SIGNAL(clicked()),this,SLOT(send_signal()));

    connect(p_mStockNumberSPinBox,SIGNAL(valueChanged(int)),this,SLOT(sum_change()));
}
//**********************************
//name:Buy_UI()
//
//input:void
//
//output:void
//
//description:绘制界面
//**********************************
void buy::Buy_UI()
{

    p_mConfirmBuyButton=new QPushButton(tr(" 确认购买"));
    p_mStockCodeLabel=new QLabel(tr("股票代码: "));
    p_mBalanceLabel=new QLabel(tr("账户余额："));
    p_mStockNumberLabel=new QLabel(tr("股数： "));
    p_mStockNumberSPinBox=new QSpinBox;
//    p_mStockNumberSPinBox->setPrefix("股数: ");
    p_mStockNumberSPinBox->setMinimum(1);
    p_mStockNumberSPinBox->setMaximum(100000);
    p_mStockNumberSPinBox->setSingleStep(1);
    p_mStockNumberSPinBox->setValue(1);
    p_mStockNumberSPinBox-> setSuffix(" *100股");
    p_mCurrentPriceLabel=new QLabel("股票单价");
    p_mSumLabel=new QLabel("预计总和") ;

    QHBoxLayout *p_mHLay=new QHBoxLayout;
    p_mHLay->addWidget(p_mStockNumberLabel);
    p_mHLay->addWidget(p_mStockNumberSPinBox);
    QVBoxLayout *p_mVLay=new QVBoxLayout;   
    p_mVLay->addWidget( p_mStockCodeLabel);
    p_mVLay->addWidget( p_mCurrentPriceLabel);
//    p_mVLay->addWidget( p_mStockNumberSPinBox);
    p_mVLay->addLayout(p_mHLay);
    p_mVLay->addWidget( p_mSumLabel);
    p_mVLay->addWidget( p_mBalanceLabel);
    p_mVLay->addWidget( p_mConfirmBuyButton);
    setLayout(p_mVLay);
    setWindowTitle("购买股票");//设置窗体标题

}
//**********************************
//name:set_code
//
//input:QString m_code   读取的股票代码
//
//output:void
//
//description:设置股票代码
//**********************************
void buy::set_code(QString m_code)
{
    m_code1=m_code;
    p_mStockCodeLabel->setText("股票代码： "+m_code1);
}
//**********************************
//name:set_price
//
//input:QString m_price  读取的股票价格
//
//output:void
//
//description:设置股票单价
//**********************************
void buy::set_price(QString m_price)
{
    m_price1=m_price;
    p_mCurrentPriceLabel->setText("股票单价: "+m_price1+" 元");
}
//**********************************
//name:set_sum()
//
//input:
//
//output:void
//
//description:设置总和
//**********************************
void buy::set_sum()
{
    double price=m_price1.toDouble();
    qDebug()<<m_price1;
    qDebug()<<price;
    int stock_number=p_mStockNumberSPinBox->value();
    qDebug()<<stock_number;
    p_mSumLabel->setText("预计总和: "+QString::number(stock_number*price/100)+" 万元");
}
//**********************************
//name:set_balance
//
//input:float balance 余额
//
//output:void
//
//description:设置余额
//**********************************
void buy::set_balance(float balance)
{
    if(balance>=100000000)
    {
          p_mBalanceLabel->setText("账户余额："+QString::number(balance/100000000)+" 亿元");

    }
    else
    {
         p_mBalanceLabel->setText("账户余额："+QString::number(balance/10000)+" 万元");
    }
    m_MaxBuyNumber=ceil(balance/(100*m_price1.toFloat()));
    p_mStockNumberSPinBox->setMaximum(m_MaxBuyNumber);
    qDebug()<<m_MaxBuyNumber;

}
//**********************************
//name:send_signal()
//
//input:
//
//output:void
//
//description:发送信号
//**********************************
void buy::send_signal()
{
    emit signal_to_query();
    send_stockbuy_number();
}
//**********************************
//name:send_stockbuy_number()
//
//input:
//
//output:void
//
//description:发送购买数量
//**********************************
int buy::send_stockbuy_number()
{
    return p_mStockNumberSPinBox->value();
}
//**********************************
//name:sum_change()
//
//input:
//
//output:void
//
//description:总和变化槽函数
//**********************************
void buy::sum_change()
{

    int stock_number=p_mStockNumberSPinBox->value();
    if(stock_number>=m_MaxBuyNumber)
    {
        qDebug()<<"输入无效";
        QString dlgTitle="输入无效";
        QString strInfo="购买总和应小于账户余额";
        //弹出警告框
        QMessageBox::warning(this, dlgTitle, strInfo);
        {
            return;
        }
    }
    double price=m_price1.toDouble();//转换数据格式
    double sum=(stock_number*price/100);
    if(sum>=10000)
    {
        p_mSumLabel->setText("预计总和: "+QString::number(sum/10000)+" 亿元");

    }
    else
    {
        p_mSumLabel->setText("预计总和: "+QString::number(sum)+" 万元");
    }
}

