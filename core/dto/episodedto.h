#ifndef EPISODEDTO_H
#define EPISODEDTO_H

#include <QStringList>

#include <core_global.h>

class QJsonDocument;
class CharacterDTO;
class CORE_EXPORT EpisodeDTO
{
public:
    EpisodeDTO(const QStringList& charactersIds);
    ~EpisodeDTO();

    static EpisodeDTO* fromJson(const QJsonDocument& jsonDocument);

    QStringList charactersIds() const;
    void setCharactersIds(const QStringList& charactersIds);

    QList<CharacterDTO*> characters() const;
    void setCharacters(const QList<CharacterDTO*>& newCharacters);

private:
    QStringList _charactersIds;
    QList<CharacterDTO*> _characters;
};

#endif // EPISODEDTO_H
