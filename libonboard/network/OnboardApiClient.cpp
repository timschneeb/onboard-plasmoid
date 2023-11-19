#include "OnboardApiClient.h"
#include "HttpException.h"

#include <QDir>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkAccessManager>

using namespace QtPromise;

OnboardApiClient::OnboardApiClient(QObject *parent) : QObject(parent) {}

QtPromise::QPromise<QString> OnboardApiClient::getStatus()
{
    return retrieveContent("/status");
}

QtPromise::QPromise<QString> OnboardApiClient::getTripInfo()
{
    return retrieveContent("/tripInfo/trip");
}

QtPromise::QPromise<QString> OnboardApiClient::getConnections(QString evaId)
{
    return retrieveContent("/tripInfo/connection/" + evaId);
}

QtPromise::QPromise<QString> OnboardApiClient::retrieveContent(QString urlPath)
{
    return QPromise<QString>{[&](
            const QtPromise::QPromiseResolve<QString>& resolve,
            const QtPromise::QPromiseReject<QString>& reject) {

            QNetworkAccessManager* nam = new QNetworkAccessManager();
            nam->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);

            auto reqProto = QNetworkRequest(QUrl(ONBOARD_BASE_URL + urlPath));
            reqProto.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::RedirectPolicy::NoLessSafeRedirectPolicy);

            QtPromise::connect(nam, &QNetworkAccessManager::finished).then([=](QNetworkReply *reply) {
                 if(reply->error() != QNetworkReply::NoError)
                 {
                     throw HttpException(999, reply->errorString());
                 }

                 QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                 QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);

                 if (statusCode.toInt() == 200)
                 {
                     QString response = reply->readAll();
                     if(response.length() < 1) {
                         throw HttpException(204, "Server returned empty response. Are you connected to a supported train WIFI hotspot?");
                     }

                     resolve(response);
                 }
                 else
                 {
                     throw HttpException(statusCode.toInt(), reason.toString());
                 }
            }).fail([reject](const HttpException& error) {
                    reject(error);
            }).finally([nam]{
                    nam->deleteLater();
            });

            nam->get(reqProto);
        }
    };
}
