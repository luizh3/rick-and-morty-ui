#include "episodecontroller.h"

#include <service/episodeservice.h>

EpisodeController::EpisodeController()
    : _episodeService{new EpisodeService()}
{}

EpisodeController::~EpisodeController() = default;

EpisodeDTO *EpisodeController::findById(const QString &episodeId) const
{
    return _episodeService->findById(episodeId);
}
