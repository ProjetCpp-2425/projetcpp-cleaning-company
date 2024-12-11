#ifndef SMS_H
#define SMS_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include <QDebug>
#include <QByteArray>
#include <QCryptographicHash>
#include <memory>

class SMS {
public:
    SMS(const QString& accountSID, const QString& authToken, const QString& from);
    void sendSMS(const QString& to, const QString& message) const;

private:

    QString accountSID;
    QString authToken;
    QString from;

    QByteArray createAuthorizationHeader() const;
};

#endif // SMS_H
