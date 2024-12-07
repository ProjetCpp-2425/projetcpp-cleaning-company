#ifndef ARDUINOMANAGER_H
#define ARDUINOMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QStringList>

class ArduinoManager : public QObject
{
    Q_OBJECT

public:
    explicit ArduinoManager(QObject *parent = nullptr);
    ~ArduinoManager();

    bool connecter(const QString &portName);
    void envoyerServices(const QStringList &services);

private:
    QSerialPort *arduino;
};

#endif // ARDUINOMANAGER_H
