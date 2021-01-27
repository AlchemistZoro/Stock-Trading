//****************************************
//文件名：           SinaFinanceAPI.h
//版本              1.0
//目的及主要功能      调用api
//创建日期           2020.9.10
//修改日期           2020.9.20
//作者              ctrlC
//联系方式           关注bilibili账号：肯抽C
//****************************************
#pragma once
#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QPixmap>


class SinaFinanceAPI
{
public:
    SinaFinanceAPI(void);//初始化
	~SinaFinanceAPI(void);
	//从指定api地址获取信息
    void requestStockInfo(QString urlStr);//发送请求
    void downloadFromUrl(QString urlStr);//下载图片
    //取出对象
    QString getStockInfoString(){return m_stockInfo;}
    QPixmap getPic(){return m_pixmap;};
    //写入文件
	void writeFile(QString filename);
private:
    QString m_stockInfo;//股票信息
    QString m_URL;//股票url
    QPixmap m_pixmap;//图片
};
