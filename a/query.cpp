#include "query.h"
#include "ViewerContent.h"

#include <QDebug>
#include    <QHBoxLayout>
#include    <QVBoxLayout>
#include    <QMessageBox>
#include    <QDir>
#include    <QDateTime>
#include    <QThread>

//**********************************
//name:Query_UI()
//
//input:
//
//output:void
//
//description:绘制ui
//**********************************
void Query::Query_UI()
{
    //json_read();
//    json_write();
    this->setFixedSize(1400,400);
    this->move(300,300);
    p_mToQueryButton=new QPushButton(tr("查询"));
    p_mBuyButton=new QPushButton(tr("购买"));
    p_mUserButton=new QPushButton(tr("用户"));
    p_mQueryLineEdit=new QLineEdit();
    p_mQueryLineEdit->setFixedSize(150,25);
    p_mKPictureLabel=new QLabel(tr("kpicture"));
    p_mKPictureLabel->setFixedSize(550,320);
    p_mDPictureLabel=new QLabel(tr("dpicture"));
    p_mDPictureLabel->setFixedSize(550,320);

    p_mStockIfoTextBrowser=new QTextBrowser();
    p_mStockIfoTextBrowser->setFixedSize(240,200);
    p_mStockIfoTextBrowser->setPlainText("股票信息显示窗口");

    QHBoxLayout *p_mHLay1=new QHBoxLayout;//排列方式
    p_mHLay1->addWidget(p_mQueryLineEdit);
    p_mHLay1->addWidget(p_mToQueryButton);

    QHBoxLayout *p_mHLay3=new QHBoxLayout;
    p_mHLay3->addWidget(p_mBuyButton);
    p_mHLay3->addWidget(p_mUserButton);

    QVBoxLayout *p_mVLay1=new QVBoxLayout;
    p_mVLay1->addLayout(p_mHLay1);
    p_mVLay1->addWidget(p_mStockIfoTextBrowser);
    p_mVLay1->addLayout(p_mHLay3);

    QHBoxLayout *p_mHLay2=new QHBoxLayout;   
    p_mHLay2->addWidget(p_mDPictureLabel);
    p_mHLay2->addWidget(p_mKPictureLabel);
    p_mHLay2->addLayout(p_mVLay1);



    setLayout( p_mHLay2);//设置主排列方式
}
//**********************************
//name:iniSignalSlots()
//
//input:
//
//output:void
//
//description:初始化槽函数
//**********************************
void Query::iniSignalSlots()
{


    connect(p_mBuyButton,SIGNAL(clicked()),this,SLOT(query_to_buy()));//
    connect(p_mUserButton,SIGNAL(clicked()),this,SLOT(query_to_user()));//
    connect(p_mToQueryButton, SIGNAL( returnPressed() ),this, SLOT( slot_update() ) );
    connect( p_mToQueryButton, SIGNAL( clicked() ),
        this, SLOT( slot_update()));
   // connect(p_mUserWindow->p_mSoldWindowBotton,SIGNAL(signal_write()),this,SLOT(start_write_json()));


}


//**********************************
//name:start_write_json()
//
//input:
//
//output:void
//
//description:写入文件槽函数
//**********************************
void Query::start_write_json()
{

    json_write();
}

//**********************************
//name:slot_update()
//input:
//
//output:void
//
//description:信号更新槽函数
//**********************************
void Query::slot_update()
{
    //使用正则表达式检测非法输入
    QString tailSTR=p_mQueryLineEdit->text();
    QRegExp rx("[0-9]{6}");
    int pos = tailSTR.indexOf(rx);

    qDebug()<<pos;
    if(pos<0)
    {
    qDebug("invaild input.");
    //检查是否输入有效股票代码
    QString dlgTitle="输入无效";
    QString strInfo="请输入正确的股票代码";
    QMessageBox::warning(this, dlgTitle, strInfo);

        return;
    }

    QString symbol = tailSTR.mid(pos,6);
    //qDebug(symbol);

    QString URLSTR = "http://hq.sinajs.cn/list=sh"+symbol;
    ViewerContent vct;
    vct.SetFromSinaAPI(URLSTR);
    this->updateViewer(vct);

}
//**********************************
//name:updateViewer
//
//input:ViewerContent vct  股票content类
//
//output:void
//
//description:获得股票content类的信息
//**********************************
void Query::updateViewer(ViewerContent vct)
{
    qDebug("Update Query.");

    m_vct=vct;
    this->setWindowTitle(
        //vct.p_mstock->get_stockName()
        +" "+vct.p_mstock->get_stockCode()
        +" "+vct.p_mstock->get_time()
        +" "+vct.p_mstock->get_date());
    m_code=vct.p_mstock->get_stockCode();
    m_price=vct.p_mstock->get_current();



    p_mStockIfoTextBrowser->setText("股票代码： "+vct.p_mstock->get_stockCode()+
                                    "\n\n当前价格： "+vct.p_mstock->get_current()+" 元\n\n开盘价： "
                                     +vct.p_mstock->get_openingPrice()+" 元\n\n收盘价： "
                                     +vct.p_mstock->get_turnover()+" 元\n\n最高价： "
                                     +vct.p_mstock->get_max()+" 元\n\n最低价： "
                                     +vct.p_mstock->get_min()+" 元");

    
    
    QPixmap pixmap;
    pixmap = vct.p_mstock->get_timeLinePixmap();
    pixmap.scaled(p_mKPictureLabel->size(), Qt::KeepAspectRatio);
    p_mKPictureLabel->setScaledContents(true);
    p_mKPictureLabel->setPixmap(pixmap);

    pixmap = vct.p_mstock->get_dayKLinePixmap();
    pixmap.scaled(p_mDPictureLabel->size(), Qt::KeepAspectRatio);
    p_mDPictureLabel->setScaledContents(true);
    p_mDPictureLabel->setPixmap(pixmap);

}
//**********************************
//name:value_change
//
//input:float sum 和
//
//output:void
//
//description:和改变槽函数
//**********************************
QString Query::value_change(float sum)
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
//name:calculate_currentsum()
//
//input:
//
//output:void
//
//description:计算总资产
//**********************************
void Query::calculate_currentsum()
{
    p_mperson->m_current_sum=p_mperson->m_BalanceMoney;
    qDebug()<<"balance1："<<p_mperson->m_current_sum;
    if(p_mperson->m_StockVector.size()>0)
    {
        for(int i=0;i<p_mperson->m_StockVector.size();i++)
        {
            p_mperson->m_current_sum+=(p_mperson->m_StockVector[i]->get_current()).toFloat()
                    *p_mperson->m_StockVector[i]->m_stockNumber*100;
            qDebug()<<"balance1："<<p_mperson->m_current_sum;
        }

    }
}
//**********************************
//name:output_person_info()
//
//input:
//
//output:QString 人的信息的文本
//
//description:输出人的信息
//**********************************
QString Query::output_person_info()
{
    QString person_info;
    calculate_currentsum();
    person_info="用户名字："+p_mperson->m_Name+"\n\n开户券商："+p_mperson->m_Bank+"\n\n账户余额："+value_change(p_mperson->m_BalanceMoney)
            +"\n\n初始资金："+value_change(p_mperson->m_IniMoney)+"\n\n总资产："+value_change(p_mperson->m_IniMoney);

//    for(int i=0;i<p_mperson->m_StockVector.size();i++)
//    {
//          person_info+="\n";
//        person_info+=p_mperson->m_StockVector[i]->get_stockCode();
//        person_info+="  ";
//        person_info+=QString::number(p_mperson->m_StockVector[i]->m_stockNumber);

//    }
    return person_info;
}
//**********************************
//name:query_to_buy()
//
//input:
//
//output:
//
//description:跳转到购买界面槽函数
//**********************************
void Query::query_to_buy()
{
    p_mBuyWindow = new buy();
    p_mBuyWindow->setFixedSize(240,300);
    p_mBuyWindow->set_code(m_code);
    p_mBuyWindow->set_price(m_price);
    p_mBuyWindow->set_sum();
    p_mBuyWindow->set_balance(p_mperson->m_BalanceMoney);
    connect(p_mBuyWindow, SIGNAL(signal_to_query()), this, SLOT(buy_to_query()));

    p_mBuyWindow->setWindowModality(Qt::ApplicationModal);
    p_mBuyWindow->show();



}
//**********************************
//name:buy_to_query()
//input:
//
//output:
//
//description:返回界面槽函数
//**********************************
void Query::buy_to_query()
{
    buy_stock(p_mBuyWindow->send_stockbuy_number());
    json_write();
    p_mBuyWindow->hide();

}
//**********************************
//name:query_to_user()
//
//input:
//
//output:
//
//description:前往用户界面槽函数
//**********************************
void Query::query_to_user()
{
    p_mUserWindow=new user;
    p_mUserWindow->setFixedSize(this->size());
    p_mUserWindow->move(this->pos());
    p_mUserWindow->set_info(p_mperson);
    connect(p_mUserWindow,SIGNAL(signal_write()),this,SLOT(start_write_json()));
    connect(p_mUserWindow, SIGNAL(signal_to_query()), this, SLOT(user_to_query()));
    this->hide();
    p_mUserWindow->show();


}
//**********************************
//name:user_to_query()
//
//input:
//
//output:
//
//description:用户界面返回主界面槽函数
//**********************************
void Query::user_to_query()
{
    this->move(p_mUserWindow->pos());

    p_mUserWindow->hide();
    this->show();
    //this->show();
}
//**********************************
//name:buy_stock
//
//input:int stock_number 购买股票数
//
//output:
//
//description:购买股票的操作
//**********************************
void Query::buy_stock(int stock_number)
{
   int in_vector=0;
   float sum_buy=0;
   //分情况讨论在有无股票的状态下的不同的操作逻辑
    for(int i=0;i< p_mperson->m_StockVector.size();i++)
   {
        if(p_mperson->m_StockVector[i]->get_stockCode()==m_vct.p_mstock->get_stockCode())
        {
            p_mperson->m_StockVector[i]->m_stockNumber+=stock_number;
            p_mperson->m_StockVector[i]->m_stockPrice=m_vct.p_mstock->get_current().toFloat();
            p_mperson->m_BalanceMoney-=stock_number*m_vct.p_mstock->get_current().toFloat()*100;
            in_vector=1;
        }
   }
    if(in_vector==0)
    {
        m_vct.p_mstock->m_stockNumber=stock_number;
        m_vct.p_mstock->m_stockPrice=m_vct.p_mstock->get_current().toFloat();
        p_mperson->m_StockVector.push_back(m_vct.p_mstock);
        p_mperson->m_BalanceMoney-=stock_number*m_vct.p_mstock->get_current().toFloat()*100;
    }



    p_mStockIfoTextBrowser->setText(output_person_info());

    qDebug()<<"success buy";
}
//**********************************
//name:Query
//
//input:QWidget *parent
//
//output:
//
//description:初始化
//**********************************
Query::Query(QWidget *parent)
    : QDialog(parent)
{
    p_mperson=new person;//?
     json_read();
    Query_UI(); //界面创建与布局
    iniSignalSlots(); //信号与槽的关联

    setWindowTitle("query");//设置窗体标题
}
//**********************************
//name:json_read()
//
//input:
//
//output:
//
//description:json文件读
//**********************************
void Query:: json_read()
{
    QFile loadFile(QDir::currentPath() + "/user.json");

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }

    QByteArray allData = loadFile.readAll();//读入所有数据
    loadFile.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return;
    }

    QJsonObject rootObj = jsonDoc.object();//变成qobject类型

    QStringList keys = rootObj.keys();
    for(int i = 0; i < keys.size(); i++)
    {
        qDebug() << "key" << i << " is:" << keys.at(i);
    }

    //因为是预先定义好的JSON数据格式，所以这里可以这样读取

    if(rootObj.contains("balance_money") && rootObj["balance_money"].isDouble())
    {
        p_mperson->m_BalanceMoney= rootObj["balance_money"].toInt();
        qDebug()<<"read_balance_money";
    }
    if(rootObj.contains("initial_money") && rootObj["initial_money"].isDouble())
    {
        p_mperson->m_IniMoney= rootObj["initial_money"].toInt();
        qDebug()<<"read_ini_money";
    }

    if(rootObj.contains("bank") && rootObj["bank"].isString())
    {
        p_mperson->m_Bank =rootObj["bank"].toString();
        qDebug()<<"read_bank";
    }
    if(rootObj.contains("name") && rootObj["name"].isString())
    {
        p_mperson->m_Name=rootObj["name"].toString();
        qDebug()<<"read_name";
    }

    //转换为列表的形式读取
    if(rootObj.contains("stock") && rootObj["stock"].isArray())
    {
        QJsonArray subArray = rootObj["stock"].toArray();
        for(int i = 0; i< subArray.size(); i++)
        {

                QJsonObject q_stock=subArray[i].toObject();
                stock * p_stock=new stock;
                p_stock->set_stockCode(q_stock["stock_code"].toString());
                p_stock->m_stockNumber=q_stock["stock_number"].toInt();

                p_mperson->m_StockVector.push_back(p_stock);
                    qDebug()<<p_stock->get_stockCode()<<p_stock->m_stockNumber<<q_stock["stock_number"].toInt();

        }
    }
}
//**********************************
//name:json_write()
//
//input:
//
//output:
//
//description:json文件写
//**********************************
void Query::json_write()
{
    QFile file(QDir::currentPath() + "/user.json");
        if(!file.open(QIODevice::ReadWrite)) {
            qDebug() << "File open error";
        } else {
            qDebug() <<"File open!";
        }

        // 清空文件中的原有内容
        file.resize(0);

        // 使用QJsonArray添加值，并写入文件
        QJsonObject jsonDoc;
        jsonDoc["name"]=p_mperson->m_Name;
        jsonDoc["bank"]=p_mperson->m_Bank;
        jsonDoc["initial_money"]=p_mperson->m_IniMoney;
        jsonDoc["balance_money"]=p_mperson->m_BalanceMoney;
        QJsonArray jsonArray;
        for(int i = 0; i < p_mperson->m_StockVector.size(); i++) {
            QJsonObject jsonObject;
            jsonObject.insert("stock_code", p_mperson->m_StockVector[i]->get_stockCode());
            jsonObject.insert("stock_number", p_mperson->m_StockVector[i]->m_stockNumber);
            jsonArray.append(jsonObject);
            QThread::sleep(2);
        }
        jsonDoc["stock"]=jsonArray;

        file.write(QJsonDocument( jsonDoc).toJson());
        file.close();

        qDebug() << "Write to file";

}
//**********************************
//name:~Query()
//
//input:
//
//output:
//
//description:析构函数
//**********************************
Query::~Query()
{

}
