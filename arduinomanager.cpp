#include "arduinomanager.h"
#include <QDebug>

ArduinoManager::ArduinoManager(QObject *parent) : QObject(parent), arduino(new QSerialPort(this))
{
}

ArduinoManager::~ArduinoManager()
{
    if (arduino->isOpen()) {
        arduino->close();
    }
    delete arduino;
}

bool ArduinoManager::connecter(const QString &portName)
{
    arduino->setPortName(portName);
    arduino->setBaudRate(QSerialPort::Baud9600);

    if (!arduino->open(QIODevice::ReadWrite)) {
        qDebug() << "Impossible de se connecter à" << portName << ":" << arduino->errorString();
        return false;
    }

    qDebug() << "Connecté à Arduino sur" << portName;
    return true;
}

void ArduinoManager::envoyerServices(const QStringList &services)
{
    if (arduino->isOpen()) {
        QString data = services.join(";") + ";";
        arduino->write(data.toUtf8());
        qDebug() << "Services envoyés à Arduino:" << data;
    } else {
        qDebug() << "Erreur: Arduino non connecté.";
    }
}
