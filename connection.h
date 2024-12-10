#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
<<<<<<< HEAD

class Connection
<<<<<<< HEAD
{ QSqlDatabase db;
=======
#include <QApplication>
#include <QMessageBox>


class Connection
{
    QSqlDatabase db;
>>>>>>> 09fd3e5a0a303ada44e8a58f383005db0699a00f
public:
    Connection();
    bool createconnect();
    void closeConnection();
<<<<<<< HEAD
=======
{
public:
    Connection();
    bool createconnect();
>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
=======
>>>>>>> 09fd3e5a0a303ada44e8a58f383005db0699a00f
};

#endif // CONNECTION_H
