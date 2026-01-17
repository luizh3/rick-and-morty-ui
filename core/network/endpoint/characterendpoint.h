#ifndef CHARACTERENDPOINT_H
#define CHARACTERENDPOINT_H

#include <QStringList>

class Response;
class CharacterEndpoint
{
public:
    Response* findByIds(const QStringList& charactersIds) const;
};

#endif // CHARACTERENDPOINT_H
