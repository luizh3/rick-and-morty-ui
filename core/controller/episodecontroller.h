#ifndef EPISODECONTROLLER_H
#define EPISODECONTROLLER_H

#include <QList>
#include <QString>

#include <memory>

#include <core_global.h>

class EpisodeDTO;
class EpisodeService;

class CORE_EXPORT EpisodeController
{
public:
    EpisodeController();
    ~EpisodeController();

    EpisodeDTO* findById(const QString& episodeId) const;

private:
    std::unique_ptr<EpisodeService> _episodeService;
};

#endif // EPISODECONTROLLER_H
