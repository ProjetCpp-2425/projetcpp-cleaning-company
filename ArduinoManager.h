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

    bool connecter(const QString &portName); // Connexion à l'Arduino
    void envoyerServices(const QStringList &services); // Envoie la liste des services
    QString recevoirSelection(); // Reçoit le service sélectionné par l'employé

private:
    QSerialPort *arduino;
};

#endif // ARDUINOMANAGER_H
