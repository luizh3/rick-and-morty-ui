#include "episodescreencontrol.h"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>

namespace {
constexpr const char *API_BASE_URL = "https://rickandmortyapi.com/api";
}

enum class HttpStatusCode { OK = 200, CREATED = 201, INTERNAL_SERVER_ERRO = 500 };

struct Response
{
    HttpStatusCode statusCode;
    QJsonDocument data;

    bool isSuccess() const
    {
        return statusCode == HttpStatusCode::OK || statusCode == HttpStatusCode::CREATED;
    }
};

EpisodeScreenControl::EpisodeScreenControl(QObject *parent)
    : QObject{parent}
{}

void EpisodeScreenControl::doSearch(const QString &episodeId)
{
    Response episodeResponse = findEpisodeById(episodeId);

    if (!episodeResponse.isSuccess()) {
        qInfo() << "EpisodeScreenControl::doSearch fail on search episode";
        return;
    }

    QJsonArray charactersUrlsJsonArray = episodeResponse.data["characters"].toArray();

    QStringList charactersIds = {};

    for (const QJsonValue &characterValue : charactersUrlsJsonArray) {
        const QString characterId = QUrl(characterValue.toString()).path().split("/").last();
        charactersIds.append(characterId);
    }

    Response charactersResponse = findChractersByIds(charactersIds);

    QStringList charactersNames = {};

    QJsonArray charactersJsonArray = charactersResponse.data.array();

    for (const QJsonValue &characterValue : charactersJsonArray) {
        charactersNames.append(characterValue.toObject()["name"].toString());
    }

    std::sort(charactersNames.begin(), charactersNames.end(), [](QString &first, QString &second) {
        return first.toLower() < second.toLower();
    });

    emit showCharacters(charactersNames);

    qInfo() << "EpisodeScreenControl::doSearch [CHARACTERS_NAMES]" << charactersNames;
}

// TODO migrate this code for ApiRickAndMortyEndpoint

Response EpisodeScreenControl::findEpisodeById(const QString &episodeId) const
{
    return getApiRickAndMorty(QString("episode/%0").arg(episodeId));
}

Response EpisodeScreenControl::findChractersByIds(const QStringList &charactersIds) const
{
    return getApiRickAndMorty(QString("character/%0").arg(charactersIds.join(",")));
}

Response EpisodeScreenControl::getApiRickAndMorty(const QString &dsPath) const
{
    qInfo() << "EpisodeScreenControl::doSearch [DS_PATH]" << dsPath;

    QNetworkAccessManager networkAccess;

    const QString dsUrl = QString("%0/%1").arg(API_BASE_URL, dsPath);

    qInfo() << "EpisodeScreenControl::doSearch [DS_URL]" << dsUrl;

    QNetworkReply *reply = networkAccess.get(QNetworkRequest(QUrl(dsUrl)));

    QEventLoop wait;

    QObject::connect(reply, &QNetworkReply::finished, &wait, &QEventLoop::quit);

    wait.exec();

    if (reply->error() != QNetworkReply::NetworkError::NoError) {
        return {HttpStatusCode::INTERNAL_SERVER_ERRO, {}};
    }

    const HttpStatusCode statusCode = HttpStatusCode(
        reply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt());

    return {statusCode, QJsonDocument::fromJson(reply->readAll())};
}
