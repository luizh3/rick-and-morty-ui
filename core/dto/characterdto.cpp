#include "characterdto.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

CharacterDTO::CharacterDTO(const QString &name)
    : _name{name}
{}

QString CharacterDTO::name() const
{
    return _name;
}

void CharacterDTO::setName(const QString &name)
{
    if (_name == name) {
        return;
    }

    _name = name;
    emit nameChanged();
}

QList<CharacterDTO *> CharacterDTO::fromJson(const QJsonDocument &jsonDocument)
{
    QList<CharacterDTO *> characters = {};

    const QJsonArray charactersJsonArray = jsonDocument.array();

    for (const QJsonValue &characterValue : charactersJsonArray) {
        characters.append(new CharacterDTO(characterValue.toObject()["name"].toString()));
    }

    return characters;
}
