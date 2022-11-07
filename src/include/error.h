#pragma once
#include <stdio.h>

typedef struct Error {
    enum ErrorType {
        ERROR_NONE = 0,
        ERROR_TYPE,
        ERROR_ARGS,
        ERROR_SYNTAX,
        ERROR_GENERIC
    } type;
    char* msg;
} Error;

void printError(Error err);

#define CREATE_ERROR(err, t, m)    \
        (err).type = (t);          \
        (err).msg = (m);
