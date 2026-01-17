#include "response.h"

Response::Response(const HttpStatusCode status, const QJsonDocument &jsonDocument)
    : _status{status}
    , _data{jsonDocument}
{}

QJsonDocument Response::data() const
{
    return _data;
}

void Response::setData(const QJsonDocument &data)
{
    _data = data;
}

HttpStatusCode Response::status() const
{
    return _status;
}

void Response::setStatus(HttpStatusCode status)
{
    _status = status;
}

bool Response::isSuccess() const
{
    return _status == HttpStatusCode::OK || _status == HttpStatusCode::CREATED;
}
