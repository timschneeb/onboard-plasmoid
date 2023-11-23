#ifndef ONBOARDAPICLIENT_H
#define ONBOARDAPICLIENT_H

#include <QtPromise>
#include <QObject>
#include <QNetworkAccessManager>

class OnboardApiClient : public QObject
{
    Q_OBJECT
public:
    explicit OnboardApiClient(const QString& baseUrl, QObject *parent = nullptr);

    QtPromise::QPromise<QString> getStatus();
    QtPromise::QPromise<QString> getTripInfo();
    QtPromise::QPromise<QString> getConnections(QString evaId);

    QString baseUrl() const;
    void setBaseUrl(const QString &newBaseUrl);

private:
    QtPromise::QPromise<QString> retrieveContent(QString urlPath);

    QString _baseUrl;
};

#endif // ONBOARDAPICLIENT_H
