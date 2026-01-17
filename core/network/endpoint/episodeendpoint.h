#ifndef EPISODEENDPOINT_H
#define EPISODEENDPOINT_H

#include <QString>

class Response;
class EpisodeEndpoint
{
public:
    Response* findById(const QString& episodeId) const;
};

#endif // EPISODEENDPOINT_H
