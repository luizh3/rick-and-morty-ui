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

        // TODO If in the future don't want lock the UI, run with Qt::concurrent.
        _episodeDTO.reset(_episodeController->findById(episodeId));

        QList<CharacterDTO *> characters = _episodeDTO->characters();

        sortCharactersByName(characters);

        emit showCharacters(QVariant::fromValue(characters));

    } catch (std::runtime_error &exception) {
        qInfo() << "EpisodeScreenControl::doSearch failed on fetch episode! [WHAT]"
                << exception.what();

        emit messageError(tr(exception.what()));
    }

    qInfo() << "EpisodeScreenControl::doSearch";
}

void EpisodeScreenControl::sortCharactersByName(QList<CharacterDTO *> &characters) const
{
    qInfo() << "EpisodeScreenControl::sortCharactersByName [CHARACTERS_COUNT]"
            << characters.count();

    std::sort(characters.begin(), characters.end(), [](CharacterDTO *first, CharacterDTO *second) {
        return first->name().toLower() < second->name().toLower();
    });

    qInfo() << "EpisodeScreenControl::sortCharactersByName";
}
