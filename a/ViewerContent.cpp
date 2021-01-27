#include "ViewerContent.h"
#include "SinaFinanceAPI.h"

#include <QtCore>   
#include <QTextCodec>
#include <QDebug>
#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream> 
using namespace std;

ViewerContent::ViewerContent(void)
{
}

ViewerContent::~ViewerContent(void)
{
}
//使用新浪API提供的csv格式的字符串更新生成ViewerContent对象
//**********************************
//name:SetFromSinaAPI
//
//
//output:QString urlStr 网址
//
//description:解析api返回数据
//**********************************
void ViewerContent::SetFromSinaAPI(QString urlStr)
{
    qDebug("Set viewer content from SinaAPI.");//?
	SinaFinanceAPI sfAPI;
    p_mstock=new stock;
	sfAPI.requestStockInfo(urlStr);
	QString stockInfo = sfAPI.getStockInfoString();

    p_mstock->set_stockName(stockInfo);
    QString symbol = urlStr.mid(27,6);
    p_mstock->set_stockCode("sh"+symbol);

    sfAPI.downloadFromUrl("http://image.sinajs.cn/newchart/min/n/sh"
                          + symbol +".gif");
    p_mstock->set_timeLinePixmap( sfAPI.getPic());

    sfAPI.downloadFromUrl("http://image.sinajs.cn/newchart/daily/n/sh"
                          + symbol +".gif");
    p_mstock->set_dayKLinePixmap( sfAPI.getPic());

    p_mstock->set_time(stockInfo.section(',',30,30));
    p_mstock->set_date(stockInfo.section(',',31,31));


    p_mstock->set_openingPrice(stockInfo.section(',',1,1));
    p_mstock->set_current(stockInfo.section(',',3,3));
    //m_amount=stockInfo.section(',',8,8);
	//交易量 精度为整数
    p_mstock->set_turnover(stockInfo.section(',',2,2));
    p_mstock->set_max(stockInfo.section(',',4,4));
    p_mstock->set_min(stockInfo.section(',',5,5));
	//涨停价 和 跌停价

}
