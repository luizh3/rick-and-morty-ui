#ifndef EPISODESCREENCONTROL_H
#define EPISODESCREENCONTROL_H

#include <QObject>
#include <QVariant>

class EpisodeDTO;
class CharacterDTO;
class EpisodeController;
class EpisodeScreenControl : public QObject
{
    Q_OBJECT
public:
    EpisodeScreenControl();
    ~EpisodeScreenControl();

    Q_INVOKABLE void doSearch(const QString &episodeId);

signals:
    void showCharacters(QVariant characters);
    void messageError(const QString &message);
    void showLoading(const QString &message);

private:
    void sortCharactersByName(QList<CharacterDTO *> &characters) const;

    std::unique_ptr<EpisodeController> _episodeController;
    std::unique_ptr<EpisodeDTO> _episodeDTO;
};

#endif // EPISODESCREENCONTROL_H
