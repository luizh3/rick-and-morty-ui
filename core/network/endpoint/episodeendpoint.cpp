#include "episodeendpoint.h"

#include <network/httpclient.h>

Response *EpisodeEndpoint::findById(const QString &episodeId) const
{
    return HttpClient::get(QString("%0/%1").arg("episode", episodeId));
}
