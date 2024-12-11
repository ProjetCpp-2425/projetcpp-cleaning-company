#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "Connection.h"
#include <QWidget>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // Create a database connection object
    Connection c;

    // Attempt to establish the connection
    bool test = c.createconnect();

    // Create a MainWindow object
    MainWindow w;

    // Check if the connection was successful
    if (test)
    {
        // Show the main window
        w.show();

        // Show a success message
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        // Show an error message if the connection failed
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    // Start the event loop
    return a.exec();
}
