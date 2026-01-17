#include "httpclient.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QEventLoop>
#include <QJsonDocument>

#include "response/httpstatuscode.h"
#include "response/response.h"

// TODO migrate for another local
namespace {
constexpr const char *DEFAULT_API_BASE_URL = "https://rickandmortyapi.com/api";
}

Response *HttpClient::get(const QString &dsPath)
{
    qInfo() << "HttpClient::get [DS_PATH]" << dsPath;

    QNetworkAccessManager networkAccess;

    const QString dsBaseUrl = qEnvironmentVariable("API_BASE_URL", DEFAULT_API_BASE_URL);

    QNetworkReply *reply = networkAccess.get(
        QNetworkRequest(QString("%0/%1").arg(dsBaseUrl, dsPath)));

    QEventLoop wait;

    QObject::connect(reply, &QNetworkReply::finished, &wait, &QEventLoop::quit);

    wait.exec();

    if (reply->error() != QNetworkReply::NetworkError::NoError) {
        qInfo() << "HttpClient::get fail on make request [ERROR_STRING]" << reply->errorString();
        reply->deleteLater();
        return new Response(HttpStatusCode::INTERNAL_SERVER_ERRO, {});
    }

    const int statusCode = reply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute)
                               .toInt();

    reply->deleteLater();

    qInfo() << "HttpClient::get [STATUS_CODE]" << statusCode;

    return new Response(HttpStatusCode(statusCode), QJsonDocument::fromJson(reply->readAll()));
}
