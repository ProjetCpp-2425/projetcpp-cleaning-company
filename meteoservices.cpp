#include "meteoservices.h"

MeteoService::MeteoService(QObject *parent)
    : QObject(parent),
      manager(new QNetworkAccessManager(this)) // Initialisation du gestionnaire
{
    connect(manager, &QNetworkAccessManager::finished, this, &MeteoService::gestionReponse);
}

void MeteoService::getMeteoActuelle(const QString &ville) {
    QString endpoint = "http://api.weatherstack.com/current";
    QString key = "1b3266fd75e21f568797c64a610413fe";
    QString url = QString("%1?access_key=%2&query=%3").arg(endpoint).arg(key).arg(ville);

    // Créez un objet QNetworkRequest avec l'URL correctement formée
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    // Effectuez la requête GET avec un objet QNetworkRequest valide
    manager->get(request);
}


void MeteoService::gestionReponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Erreur dans la requête météo :" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray reponse = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(reponse);

    if (!doc.isObject()) {
        qWarning() << "Réponse non valide (pas un objet JSON).";
        reply->deleteLater();
        return;
    }

    QJsonObject json = doc.object();
    if (json.contains("current")) {
        QJsonObject current = json.value("current").toObject();
        double temperature = current.value("temperature").toDouble();
        QString description = current.value("weather_descriptions").toArray().first().toString();

        emit meteoRecue(temperature, description); // Émettre le signal avec les données

        qDebug() << "Température actuelle :" << temperature;
        qDebug() << "Description :" << description;
    } else {
        qWarning() << "Aucune donnée météo trouvée dans la réponse.";
    }

    reply->deleteLater();
}
