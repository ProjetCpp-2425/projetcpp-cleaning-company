#include "connection.h"
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
