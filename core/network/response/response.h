#ifndef RESPONSE_H
#define RESPONSE_H

#include <QJsonDocument>

#include "httpstatuscode.h"

class Response
{
public:
    Response(const HttpStatusCode status, const QJsonDocument &jsonDocument);

    HttpStatusCode status() const;
    void setStatus(HttpStatusCode newStatus);

    QJsonDocument data() const;
    void setData(const QJsonDocument &newData);

    bool isSuccess() const;

private:
    HttpStatusCode _status;
    QJsonDocument _data;
};

#endif // RESPONSE_H
