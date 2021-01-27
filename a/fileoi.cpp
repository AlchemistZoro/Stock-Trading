#include "fileoi.h"

fileoi::fileoi(QObject *parent) : QObject(parent)
{

}
void json_read()
{
    QFile loadFile("A:\\deskto\\1.json");

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }

    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return;
    }

    QJsonObject rootObj = jsonDoc.object();

    QStringList keys = rootObj.keys();
    for(int i = 0; i < keys.size(); i++)
    {
        qDebug() << "key" << i << " is:" << keys.at(i);
    }

    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if(rootObj.contains("first fruit") && rootObj["first fruit"].isObject())
    {
        QJsonObject subObj = rootObj["first fruit"].toObject();
        if (subObj.contains("describe") && subObj["describe"].isString())
        {
            qDebug() << "describe is:" << subObj["describe"].toString();
        }
        if (subObj.contains("icon") && subObj["icon"].isString())
        {
            qDebug() << "icon is:" << subObj["icon"].toString();
        }
        if (subObj.contains("name") && subObj["name"].isString())
        {
            qDebug() << "name is:" << subObj["name"].toString();
        }
    }

    if(rootObj.contains("second fruit") && rootObj["second fruit"].isObject())
    {
        QJsonObject subObj = rootObj["second fruit"].toObject();
        if (subObj.contains("describe") && subObj["describe"].isString())
        {
            qDebug() << "describe is:" << subObj["describe"].toString();
        }
        if (subObj.contains("icon") && subObj["icon"].isString())
        {
            qDebug() << "icon is:" << subObj["icon"].toString();
        }
        if (subObj.contains("name") && subObj["name"].isString())
        {
            qDebug() << "name is:" << subObj["name"].toString();
        }
    }

    if(rootObj.contains("three fruit array") && rootObj["three fruit array"].isArray())
    {
        QJsonArray subArray = rootObj.value("three fruit array").toArray();
        for(int i = 0; i< subArray.size(); i++)
        {
            if (subArray[i].isString())
            {
                qDebug() << i<<" value is:" << subArray.at(i).toString();
            }
        }
    }

}
void json_write(person* the_user)
{

}
