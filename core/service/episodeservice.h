#ifndef EPISODESERVICE_H
#define EPISODESERVICE_H

#include <QList>
#include <QString>

#include <memory>

class EpisodeDTO;
class EpisodeEndpoint;
class CharacterEndpoint;
class EpisodeService
{
public:
    EpisodeService();
    ~EpisodeService();

    EpisodeDTO* findById(const QString& episodeId) const;

private:
    std::unique_ptr<EpisodeEndpoint> _episodeEndpoint;
    std::unique_ptr<CharacterEndpoint> _characterEndpoint;
};

#endif // EPISODESERVICE_H
