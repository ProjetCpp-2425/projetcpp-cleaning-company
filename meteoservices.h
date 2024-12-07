#ifndef METEO_SERVICE_H
#define METEO_SERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class MeteoService : public QObject {
    Q_OBJECT

public:
    explicit MeteoService(QObject *parent = nullptr);
    void getMeteoActuelle(const QString &ville); // Fonction pour demander la météo

signals:
    void meteoRecue(double temperature, QString description); // Signal émis après traitement

private slots:
    void gestionReponse(QNetworkReply *reply); // Traite la réponse

private:
    QNetworkAccessManager *manager; // Gestionnaire réseau
};

#endif // METEO_SERVICE_H
