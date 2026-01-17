#include "episodedto.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QUrl>

EpisodeDTO::EpisodeDTO(const QStringList &charactersIds)
    : _charactersIds{charactersIds}
    , _characters{}
{}

EpisodeDTO::~EpisodeDTO()
{
    qDeleteAll(_characters);
}

EpisodeDTO *EpisodeDTO::fromJson(const QJsonDocument &jsonDocument)
{
    QStringList charactersIds = {};

    const QJsonArray charactersJsonArray = jsonDocument["characters"].toArray();

    for (const QJsonValue &characterJsonValue : charactersJsonArray) {
        const QString characterId = QUrl(characterJsonValue.toString()).path().split("/").last();
        charactersIds.append(characterId);
    }

    return new EpisodeDTO(charactersIds);
}

QStringList EpisodeDTO::charactersIds() const
{
    return _charactersIds;
}

void EpisodeDTO::setCharactersIds(const QStringList &charactersIds)
{
    _charactersIds = charactersIds;
}

QList<CharacterDTO *> EpisodeDTO::characters() const
{
    return _characters;
}

void EpisodeDTO::setCharacters(const QList<CharacterDTO *> &characters)
{
    _characters = characters;
}
