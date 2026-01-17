#include "characterendpoint.h"

#include <network/httpclient.h>

Response *CharacterEndpoint::findByIds(const QStringList &charactersIds) const
{
    const QString &dsUrl = QString("%0/%1").arg("character", charactersIds.join(","));
    return HttpClient::get(dsUrl);
}
