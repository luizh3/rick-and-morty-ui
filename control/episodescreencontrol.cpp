#include "episodescreencontrol.h"

#include <core/dto/characterdto.h>
#include <core/dto/episodedto.h>

#include <core/controller/episodecontroller.h>

EpisodeScreenControl::EpisodeScreenControl()
    : _episodeController{new EpisodeController()}
    , _episodeDTO{}
{}

EpisodeScreenControl::~EpisodeScreenControl() = default;

void EpisodeScreenControl::doSearch(const QString &episodeId)
{
    qInfo() << "EpisodeScreenControl::doSearch [EPISODE_ID]" << episodeId;

    // TODO This exception should be handled in the controller.

    try {
        emit showLoading(tr("Aguarde..."));

        // TODO If in the future you don't want to go through the UI, run with Qt::concurrent.
        _episodeDTO.reset(_episodeController->findById(episodeId));

        emit showCharacters(QVariant::fromValue(_episodeDTO->characters()));

    } catch (std::runtime_error &exception) {
        qInfo() << "EpisodeScreenControl::doSearch failed on fetch episode! [WHAT]"
                << exception.what();

        emit messageError(tr(exception.what()));
    }

    qInfo() << "EpisodeScreenControl::doSearch";
}
