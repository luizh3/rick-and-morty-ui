#ifndef EPISODESCREENCONTROL_H
#define EPISODESCREENCONTROL_H

#include <QObject>
#include <QVariant>

class Response;
class EpisodeScreenControl : public QObject
{
    Q_OBJECT
public:
    explicit EpisodeScreenControl(QObject *parent = nullptr);

    Q_INVOKABLE void doSearch(const QString &episodeId);

signals:
    void showCharacters(QVariant characters);

private:
    Response findEpisodeById(const QString &episodeId) const;
    Response findChractersByIds(const QStringList &charactersIds) const;
    Response getApiRickAndMorty(const QString &dsPath) const;
};

#endif // EPISODESCREENCONTROL_H
