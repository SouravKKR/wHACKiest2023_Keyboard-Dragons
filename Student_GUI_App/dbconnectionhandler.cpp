#include "dbconnectionhandler.h"
#include<QSqlError>
#include<iostream>

DBConnectionHandler::DBConnectionHandler()
{

}

DBConnectionHandler::DBConnectionHandler(QString db, QString host, QString user, QString pass)
{
    Database = db;
    Host = host;
    User = user;
    Password= pass;
}

bool DBConnectionHandler::Connect()
{
       db = QSqlDatabase::addDatabase("QMYSQL", "DB");
       db.setHostName(Host);
       db.setDatabaseName(Database);
       db.setUserName(User);
       db.setPassword(Password);
       if(db.open())
       {
            Connected =true;
            exit(0);
       }
       else
       {
           QSqlError error = db.lastError();
           auto temp = error.text();
           std::string temp1 =temp.toStdString();
           std::cout<<temp1<<"\n";
       }

       return Connected;
}
