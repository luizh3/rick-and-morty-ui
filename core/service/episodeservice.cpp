#include "episodeservice.h"

#include <dto/characterdto.h>
#include <dto/episodedto.h>

#include <network/response/response.h>

#include <network/endpoint/characterendpoint.h>
#include <network/endpoint/episodeendpoint.h>

EpisodeService::EpisodeService()
    : _episodeEndpoint{new EpisodeEndpoint()}
    , _characterEndpoint{new CharacterEndpoint()}
{}

EpisodeService::~EpisodeService() = default;

EpisodeDTO* EpisodeService::findById(const QString& episodeId) const
{
    qInfo() << "EpisodeService::findById [EPISODE_ID]" << episodeId;

    std::unique_ptr<Response> episodeResponse(_episodeEndpoint->findById(episodeId));

    if (!episodeResponse->isSuccess()) {
        qCritical() << "EpisodeService::findById failed on find episode";
        throw std::runtime_error("Failed on search episode!");
    }

    EpisodeDTO* episodeDTO = EpisodeDTO::fromJson(episodeResponse->data());

    std::unique_ptr<Response> charactersResponse(
        _characterEndpoint->findByIds(episodeDTO->charactersIds()));

    if (!charactersResponse->isSuccess()) {
        qCritical() << "EpisodeService::findById failed on find characters";
        throw std::runtime_error("Failed on search characters!");
    }

    episodeDTO->setCharacters(CharacterDTO::fromJson(charactersResponse->data()));

    qInfo() << "EpisodeService::findById";

    return episodeDTO;
}
