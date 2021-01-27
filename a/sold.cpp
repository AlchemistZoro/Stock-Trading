#include "sold.h"
#include    <QHBoxLayout>
#include    <QVBoxLayout>
#include    <QDebug>
#include    <QMessageBox>
//**********************************
//name:sold
//
//input:QWidget *parent
//
//output:
//
//description:初始化
//**********************************
sold::sold(QWidget *parent) : QWidget(parent)
{
    Sold_UI();
    iniSignalSlots();
}

//**********************************
//name:send_signal()
//
//input:
//
//output:
//
//description:发送信号
//**********************************
void sold::send_signal()
{

    emit signal_to_user();
}


//**********************************
//name:Sold_UI()
//
//input:
//
//output:
//
//description:更新界面
//**********************************
void sold::Sold_UI()
{
    p_mStockInfoLabel=new QLabel(tr("股票信息"));
//    p_mPirceBuyLabel=new QLabel(tr("买入单价"));
    p_mPriceCurrentLabel=new QLabel(tr("当前单价"));
    p_mNumberBuyLabel=new QLabel(tr("买入股数"));
    p_mNumberSoldLabel=new QLabel(tr("卖出股数"));
    p_mNumberSoldSpinBox=new QSpinBox();
    p_mNumberSoldSpinBox->setMinimum(1);
    p_mNumberSoldSpinBox->setMaximum(100000);
    p_mNumberSoldSpinBox->setSingleStep(1);
    p_mNumberSoldSpinBox->setValue(1);
    p_mNumberSoldSpinBox-> setSuffix(" *100股");
    p_mSumLabel=new QLabel(tr("预计总价"));
    p_mSoldBotton=new QPushButton(tr("确认抛售"));


    QHBoxLayout *p_mHLay=new QHBoxLayout;
    p_mHLay->addWidget(p_mNumberSoldLabel);
    p_mHLay->addWidget(p_mNumberSoldSpinBox);
    QVBoxLayout *p_mVLay=new QVBoxLayout;
    p_mVLay->addWidget( p_mStockInfoLabel);
//    p_mVLay->addWidget( p_mPirceBuyLabel);
    p_mVLay->addWidget( p_mNumberBuyLabel);
    p_mVLay->addWidget( p_mPriceCurrentLabel);
    p_mVLay->addLayout(p_mHLay);
    p_mVLay->addWidget( p_mSumLabel);
    p_mVLay->addWidget( p_mSoldBotton);
    setLayout(p_mVLay);
}

//**********************************
//name:Sold_UI()
//
//input:
//
//output:
//
//description:更新界面
//**********************************
void sold::set_sold_info(QString stock_code, QString stock_number, QString stock_price)
{
     m_SoldNumber=stock_number.toInt();
     m_CurrentPrice=stock_price.toFloat();
     m_StockCode=stock_code;
     p_mStockInfoLabel->setText("股票代码："+stock_code);

     p_mPriceCurrentLabel->setText("股票单价："+stock_price);
     p_mNumberBuyLabel->setText("持有股数: "+stock_number);
     double sum=(p_mNumberSoldSpinBox->value()*m_CurrentPrice/100);
     //根据值改变输出方式
     if(sum>=10000)
     {
         p_mSumLabel->setText("预计总和: "+QString::number(sum/10000)+" 亿元");

     }
     else
     {
         p_mSumLabel->setText("预计总和: "+QString::number(sum)+" 万元");
     }

}
//**********************************
//name:iniSignalSlots()
//
//input:
//
//output:
//
//description:连接槽函数
//**********************************
void sold::iniSignalSlots()
{
    connect(p_mSoldBotton,SIGNAL(clicked()),this,SLOT(send_signal()));
    connect(p_mNumberSoldSpinBox,SIGNAL(valueChanged(int)),this,SLOT(sum_change()));
}

//**********************************
//name:sum_change()
//input:
//
//output:
//
//description:更改总和槽函数
//**********************************
void sold::sum_change()
{
    if(p_mNumberSoldSpinBox->value()>m_SoldNumber)
    {
            p_mNumberSoldSpinBox->setValue(p_mNumberSoldSpinBox->value()-1);
            QString dlgTitle="无效操作";
            QString strInfo="抛售股票数量应当小于持仓数量！";
            QMessageBox::warning(this, dlgTitle, strInfo);
            {
                return;
            }
    }
     else
     {
        double sum=(p_mNumberSoldSpinBox->value()*m_CurrentPrice/100);
        if(sum>=10000)
        {
            p_mSumLabel->setText("预计总和: "+QString::number(sum/10000)+" 亿元");

        }
        else
        {
            p_mSumLabel->setText("预计总和: "+QString::number(sum)+" 万元");
        }
    }
}
//**********************************
//name:get_sold_info()
//
//input:
//
//output:
//
//description:获得信息槽函数
//**********************************
int sold::get_sold_info()
{
      return p_mNumberSoldSpinBox->value();
}
