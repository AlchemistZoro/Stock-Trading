#ifndef FILEOI_H
#define FILEOI_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "person.h"

class fileoi : public QObject
{
    Q_OBJECT
public:

    explicit fileoi(QObject *parent = nullptr);
    void json_read();
    void json_write(person*);

signals:

public slots:
};

#endif // FILEOI_H
