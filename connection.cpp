#include "connection.h"
<<<<<<< HEAD
#include <QDebug>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
<<<<<<< HEAD
  qDebug() << "Drivers disponibles:" << QSqlDatabase::drivers();
=======
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet_cpp");//inserer le nom de la source de données
db.setUserName("projetcpp2a32");//inserer nom de l'utilisateur
db.setPassword("mp2a32");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;







    return  test;
}
void Connection::closeConnection() { db.close(); }

=======
#include <QDebug>  // For logging

Connection::Connection() {}

bool Connection::createconnect()
{
    bool test = false;

    // Log the start of the connection attempt
    qDebug() << "Attempting to establish a connection to the database...";

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source2a32");
    db.setUserName("projetcpp2a32");
    db.setPassword("mp2a32");

    // Try to open the database connection
    if (db.open()) {
        test = true;
        qDebug() << "Database connection successful!";
    } else {
        // Log any errors if the connection fails
        qDebug() << "Database connection failed!";
        qDebug() << "Error: " << db.lastError().text();
    }

    return test;
}
>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
