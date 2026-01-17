#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>

class Response;
class HttpClient : public QObject
{
    Q_OBJECT
public:
    static Response *get(const QString &dsUrl);

signals:
};

#endif // HTTPCLIENT_H
