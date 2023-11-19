#ifndef ONBOARDAPICLIENT_H
#define ONBOARDAPICLIENT_H

#include <QtPromise>
#include <QObject>
#include <QNetworkAccessManager>

#ifndef USE_LOCAL_SERVER
#define ONBOARD_BASE_URL QString("https://iceportal.de/api1/rs")
#else
#define ONBOARD_BASE_URL QString("http://localhost:9000/api1/rs")
#endif

class OnboardApiClient : public QObject
{
    Q_OBJECT
public:
    explicit OnboardApiClient(QObject *parent = nullptr);

    QtPromise::QPromise<QString> getStatus();
    QtPromise::QPromise<QString> getTripInfo();
    QtPromise::QPromise<QString> getConnections(QString evaId);

private:
    QtPromise::QPromise<QString> retrieveContent(QString urlPath);

};

#endif // ONBOARDAPICLIENT_H
