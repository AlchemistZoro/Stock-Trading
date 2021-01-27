#include "user.h"
#include "query.h"
#include    <QHBoxLayout>
#include    <QVBoxLayout>
#include    <QDebug>
#include    <QMessageBox>
//**********************************
//name:user
//
//input:QWidget *parent
//
//output:
//
//description:构造函数
//**********************************
user::user(QWidget *parent) : QWidget(parent)
{
        User_UI();
        iniSignalSlots();
}
//**********************************
//name:User_UI()
//
//input:
//
//output:
//
//description:绘制ui
//**********************************
void user::User_UI()
{

    p_mHomeButton=new QPushButton(tr("查询"));
    p_mUpdateUserInfoBotton=new QPushButton(tr("信息更新"));
    p_mSoldWindowBotton=new QPushButton(tr("卖"));
    p_mUserInfoTextBrowser=new QTextBrowser;
    p_mUserInfoTextBrowser->setFixedSize(350,320);
    p_mPositonView=new QTableView;
    //设置表格属性
    p_mPositonView->setFixedSize(900,370);
    p_mPositonView->setSortingEnabled(true);

    model=new QStandardItemModel(p_mPositonView);
    p_mPositonView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList labels = QObject::trUtf8("股票代码,购买股数/(百股),当前价格/(元),收盘价/(元),开盘价/(元),最高价/(元),最低价/(元)").simplified().split(",");
    model->setHorizontalHeaderLabels(labels);
    p_mPositonView->setModel(model);


    QHBoxLayout *p_mHLay=new QHBoxLayout;
    p_mHLay->addWidget(p_mUpdateUserInfoBotton);
    p_mHLay->addStretch();
    p_mHLay->addWidget(p_mSoldWindowBotton);
    p_mHLay->addWidget(p_mHomeButton);

    QVBoxLayout *p_mVLay=new QVBoxLayout;
    p_mVLay->addWidget(p_mUserInfoTextBrowser);
    p_mVLay->addLayout(p_mHLay);

    QHBoxLayout *p_mHLay2=new QHBoxLayout;
    p_mHLay2->addWidget(p_mPositonView);
    p_mHLay2->addLayout(p_mVLay);

    setLayout(p_mHLay2);
    setWindowTitle("user");//设置窗体标题
    connect(p_mHomeButton,SIGNAL(clicked()),this,SLOT(send_signal()));//
}
//**********************************
//name:iniSignalSlots()
//
//input:
//
//output:
//
//description:更新槽函数
//**********************************
void user::iniSignalSlots()
{
   connect( p_mSoldWindowBotton,SIGNAL(clicked()),this,SLOT(user_to_sold())) ;
   connect(p_mUpdateUserInfoBotton,SIGNAL(clicked()),this,SLOT(update_info()));

}
//**********************************
//name:update_info()
//
//input:
//
//output:
//
//description:更新信息
//**********************************
void user::update_info()
{

    qDebug()<<"start update_info";
    if(p_mperson->m_StockVector.size()==0)
    {
        QString dlgTitle="无效操作";
        QString strInfo="没有持仓股票无法更新！";
        QMessageBox::warning(this, dlgTitle, strInfo);
        {
            return;
        }
    }
    else
    {
        //更新数据调用api；
        for(int i=0;i<p_mperson->m_StockVector.size();i++)
        {
            QString testURL = "http://hq.sinajs.cn/list="+p_mperson->m_StockVector[i]->get_stockCode();
            ViewerContent vct;
            vct.SetFromSinaAPI(testURL);
            update_onestock(i,vct);
        }
    }

    change_info();


}
//**********************************
//name:update_onestock
//
//input:int i,ViewerContent vct 股票序号，用户类
//
//output:
//
//description:更新单个股票信息
//**********************************
 void user::update_onestock(int i,ViewerContent vct)
 {
     qDebug()<<QString::number(i);
     qDebug()<<vct.p_mstock->get_stockCode();
     p_mperson->m_BalanceMoney+=100000+(vct.p_mstock->get_current().toInt()-p_mperson->m_StockVector[i]->get_current().toInt())*100*p_mperson->m_StockVector[i]->m_stockNumber;
     p_mperson->m_StockVector[i]->set_current(vct.p_mstock->get_current());
     p_mperson->m_StockVector[i]->set_turnover(vct.p_mstock->get_turnover());
     p_mperson->m_StockVector[i]->set_openingPrice(vct.p_mstock->get_openingPrice());
     p_mperson->m_StockVector[i]->set_max(vct.p_mstock->get_max());
     p_mperson->m_StockVector[i]->set_min(vct.p_mstock->get_min());

 }
 //**********************************
 //name:update_onestock
 //
 //input:
 //
 //output:
 //
 //description:发送信号
 //**********************************
void user::send_signal()
{
    emit signal_to_query();

}
//**********************************
//name:user_to_sold()
//
//input:
//
//output:
//
//description:跳转到抛售界面
//**********************************
void user::user_to_sold()
{
     int curRow = p_mPositonView->currentIndex().row();
     if(curRow<0)
     {
         QString dlgTitle="无效操作";
         QString strInfo="请选择你想要抛售的股票！";
         QMessageBox::warning(this, dlgTitle, strInfo);
         {
             return;
         }
     }

     else
     {
     p_mSoldWindow=new sold();
     p_mSoldWindow->setFixedSize(240,300);

     p_mSoldWindow->set_sold_info(model->item(curRow,0)->text(),model->item(curRow,1)->text(),model->item(curRow,2)->text());
     connect(p_mSoldWindow, SIGNAL(signal_to_user()), this, SLOT(sold_to_user()));
     p_mSoldWindow->setWindowModality(Qt::ApplicationModal);
     p_mSoldWindow->show();
     }
     qDebug()<<curRow;
}
//**********************************
//name:sold_to_user()
//
//input:
//
//output:
//
//description:返回用户界面
//**********************************
void user::sold_to_user()
{

    int sold_number=p_mSoldWindow->get_sold_info();
    qDebug()<<"sold_number"<<sold_number;
    QString sold_code=p_mSoldWindow->m_StockCode;
    qDebug()<<"sold_code"<<sold_code;
    float sold_price=p_mSoldWindow->m_CurrentPrice;
    qDebug()<<"sold_price"<<sold_price;
    sold_process(sold_code,sold_number,sold_price);


    qDebug()<<"before hide sold ";
    p_mSoldWindow->hide();

}
//**********************************
//name:sold_process
//
//input:QString sold_code,int sold_number,float sold_price
//      股票代码，抛售量，股票单价
//output:
//
//description:返回用户界面
//**********************************
void user::sold_process(QString sold_code,int sold_number,float sold_price)
{
    qDebug()<<"sold_code"<<sold_code;
    qDebug()<<"p_mperson->m_StockVector.size()"<<p_mperson->m_StockVector.size();
    for(int i=0;i<p_mperson->m_StockVector.size();i++)
    {
        qDebug()<<p_mperson->m_StockVector[i]->get_stockCode();
        if(p_mperson->m_StockVector[i]->get_stockCode()==sold_code)
        {
            p_mperson->m_BalanceMoney+=sold_number*sold_price*100;

            if(sold_number==p_mperson->m_StockVector[i]->m_stockNumber)
            {
                 p_mperson->m_StockVector.erase(p_mperson->m_StockVector.begin()+i);
                    qDebug()<<"erase";
                 qDebug()<<"p_mperson->m_StockVector.size()"<<p_mperson->m_StockVector.size();
            }
            else
            {
                p_mperson->m_StockVector[i]->m_stockNumber-=sold_number;
                qDebug()<<"cut";
            }
           break;
        }
    }
    emit signal_write();
    change_info();


}
//**********************************
//name:change_info()
//
//input:
//output:
//
//description:更新信息
//**********************************
void user::change_info()
{
    p_mUserInfoTextBrowser->setText(output_person_info());
    QStandardItem* item = 0;
   model->clear();
   QStringList labels = QObject::trUtf8("股票代码,购买股数/(百股),当前价格/(元),收盘价/(元),开盘价/(元),最高价/(元),最低价/(元)").simplified().split(",");
   model->setHorizontalHeaderLabels(labels);
    //股票代码,购买股数,当前价格,收盘价,开盘价,最高价,最低价
    if(p_mperson->m_StockVector.size()>=0)
    {

        for(int i = 0;i <p_mperson->m_StockVector.size();i++)
        {
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_stockCode());
            model->setItem(i,0,item);
            item = new QStandardItem(QString::number(p_mperson->m_StockVector[i]->m_stockNumber));
            //qDebug()<<"购买价格为："<<p_mperson->m_StockVector[i]->m_stockNumber;
            model->setItem(i,1,item);//开始插入第1行的数据
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_current());
            model->setItem(i,2,item);
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_turnover());
            model->setItem(i,3,item);
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_openingPrice());
            model->setItem(i,4,item);
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_max());
            model->setItem(i,5,item);
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_min());
            model->setItem(i,6,item);
        }


    }
    else
    {
        //model->removeRow(0);

    }
     p_mPositonView->setModel(model);
}
//**********************************
//name:set_info
//
//input:person* p_person
//output:
//
//description:设置人的信息
//**********************************
void user::set_info(person* p_person)
{
    p_mperson=p_person;
    p_mUserInfoTextBrowser->setText(output_person_info());
    QStandardItem* item = 0;

    //股票代码,购买股数,当前价格,收盘价,开盘价,最高价,最低价
    if(p_mperson->m_StockVector.size()>=0)
    {
    for(int i = 0;i <p_mperson->m_StockVector.size();i++)
        {
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_stockCode());
            model->setItem(i,0,item);
            item = new QStandardItem(QString::number(p_mperson->m_StockVector[i]->m_stockNumber));
            qDebug()<<"购买价格为："<<p_mperson->m_StockVector[i]->m_stockNumber;
            model->setItem(i,1,item);//开始插入第1行的数据
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_current());
            model->setItem(i,2,item);
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_turnover());
            model->setItem(i,3,item);
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_openingPrice());
            model->setItem(i,4,item);
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_max());
            model->setItem(i,5,item);
            item = new QStandardItem(p_mperson->m_StockVector[i]->get_min());
            model->setItem(i,6,item);
        }

    //设置背景样式，字体颜色为红色，背景样式在选中的时候是绿色
    //   p_mPositonView->setStyleSheet("QTableView { border: none;"
    //                                     "selection-background-color: #8EDE21;"
    //                                    "color: red}");

    }

     p_mPositonView->setModel(model);

}
//**********************************
//name:calculate_currentsum()
//
//input:
//output:
//
//description:计算当前抛售总和
//**********************************
void user::calculate_currentsum()
{
    p_mperson->m_current_sum=p_mperson->m_BalanceMoney;
    if(p_mperson->m_StockVector.size()>0)
    {
        for(int i=0;i<p_mperson->m_StockVector.size();i++)
        {
            p_mperson->m_current_sum+=(p_mperson->m_StockVector[i]->get_current()).toFloat()
                    *p_mperson->m_StockVector[i]->m_stockNumber*100;
        }
    }
}
//**********************************
//name:value_change
//
//input:(float sum)
//output:
//
//description:改变抛售总和
//**********************************
QString user::value_change(float sum)
{
    QString value;
    if(sum>=1.0e8)
    {
        value=QString::number(sum/1.0e8)+" 亿元";

    }
    else
    {
       value=QString::number(sum/1.0e4)+" 万元";
    }
    return value;

}
//**********************************
//name:output_person_info()
//
//
//output:输出用户信息
//
//description:返回用户界面
//**********************************
QString user::output_person_info()
{
    QString person_info;
    calculate_currentsum();
    person_info="用户名字："+p_mperson->m_Name+"\n\n开户券商："+p_mperson->m_Bank+"\n\n账户余额："+value_change(p_mperson->m_BalanceMoney)
            +"\n\n初始资金"+value_change(p_mperson->m_IniMoney)+"\n\n总资产："+value_change(p_mperson->m_current_sum);

    return person_info;

}



