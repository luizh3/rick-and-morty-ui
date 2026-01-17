#ifndef CHARACTERDTO_H
#define CHARACTERDTO_H

#include <QObject>

#include <core_global.h>

class CORE_EXPORT CharacterDTO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
public:
    CharacterDTO(const QString &name);

    QString name() const;
    void setName(const QString &newName);

    static QList<CharacterDTO *> fromJson(const QJsonDocument &jsonDocument);

signals:
    void nameChanged();

private:
    QString _name;
};

#endif // CHARACTERDTO_H
