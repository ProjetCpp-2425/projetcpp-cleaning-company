#include "connection.h"
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

