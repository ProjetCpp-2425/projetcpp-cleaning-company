#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
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
}
