#include<QString>
#include<QSql>
#include<QSqlDatabase>
#include<QSqlDriver>

#ifndef DBCONNECTIONHANDLER_H
#define DBCONNECTIONHANDLER_H


class DBConnectionHandler
{
private:
    QString Host ="", Database="", User="", Password="";
    QSqlDatabase db;
    bool Connected = false;

public:
    DBConnectionHandler();
    DBConnectionHandler(QString db, QString host, QString user, QString pass);
    bool Connect();

};

#endif // DBCONNECTIONHANDLER_H
