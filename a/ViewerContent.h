//****************************************
//文件名：          ViewerContent.h
//版本              1.0
//目的及主要功能      调用api
//创建日期           2020.9.10
//修改日期           2020.9.20
//作者              ctrlC
//联系方式           关注bilibili账号：肯抽C
//****************************************

#pragma once
#pragma execution_character_set("utf-8")
#include <QString>
#include <QMap>
#include <QPixmap>
#include "stock.h"
class ViewerContent
{
public:
    ViewerContent(void);//初始化
	~ViewerContent(void);
	//通过新浪API生成content的数据
    void SetFromSinaAPI(QString urlStr);//正则化api数据
     stock *p_mstock;
signals:




	
};
