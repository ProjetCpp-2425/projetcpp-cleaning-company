<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 5482a8d21bc36440840a90978f288100425a78fa
=======
>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
<<<<<<< HEAD
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test=c.createconnect();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
=======
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;

    // Log the start of the connection attempt
    qDebug() << "Attempting to establish a database connection...";

    bool test = c.createconnect();

    MainWindow w;

    if (test) {
        // Connection was successful
        w.show();
        qDebug() << "Connection successful. Opening Main Window.";

    } else {
        // Connection failed
        qDebug() << "Connection failed. Displaying error message.";
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                    QObject::tr("Connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    // Log the final step of the application execution
    qDebug() << "Entering application event loop (a.exec()).";

    return a.exec();  // Start the Qt application event loop
>>>>>>> 86f09a4b71d8b3819662797bc776ea2ffbc04303
}
