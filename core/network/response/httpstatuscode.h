#ifndef HTTPSTATUSCODE_H
#define HTTPSTATUSCODE_H

enum class HttpStatusCode : short {
    UNKNOW = -1,
    OK = 200,
    CREATED = 201,
    INTERNAL_SERVER_ERRO = 500
};

#endif // HTTPSTATUSCODE_H
