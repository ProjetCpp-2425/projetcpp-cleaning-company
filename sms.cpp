#include "sms.h"
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

SMS::SMS(const QString& accountSID, const QString& authToken, const QString& from)
    : accountSID(accountSID), authToken(authToken), from(from) {}

void SMS::sendSMS(const QString& to, const QString& message) const {
    // Construct the API URL
    QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + accountSID + "/Messages.json");

    // Create the HTTP request
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Set the authorization header
    QByteArray auth = createAuthorizationHeader();
    qDebug() << "Authorization Header: Basic " + auth;
    request.setRawHeader("Authorization", "Basic " + auth);

    // Construct the request body
    QByteArray postData;
    postData.append("To=" + QUrl::toPercentEncoding(to));
    postData.append("&From=" + QUrl::toPercentEncoding(from));
    postData.append("&Body=" + QUrl::toPercentEncoding(message));

    // Log the URL and post data
    qDebug() << "URL:" << url.toString();
    qDebug() << "Post Data:" << postData;

    // Create a network access manager
    QNetworkAccessManager manager;

    // Send the request
    std::unique_ptr<QNetworkReply> reply(manager.post(request, postData));

    // Wait for the reply
    QEventLoop loop;
    QObject::connect(reply.get(), &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "SMS sent successfully!";
        qDebug() << reply->readAll();
    } else {
        qDebug() << "Error sending SMS:" << reply->errorString();
        qDebug() << "Response:" << reply->readAll();
    }
}

QByteArray SMS::createAuthorizationHeader() const {
    QByteArray auth = QByteArray(accountSID.toUtf8() + ":" + authToken.toUtf8());
    return auth.toBase64();
}
