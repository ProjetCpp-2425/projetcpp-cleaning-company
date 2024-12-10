#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
<<<<<<< HEAD
{ QSqlDatabase db;
public:
    Connection();
    bool createconnect();
    void closeConnection();
=======
{
public:
    Connection();
    bool createconnect();
>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
};

#endif // CONNECTION_H
