#include "parser.h"

Error ok = { ERROR_NONE, "ok"};

Error lex(char* src, char** beg, char** end) {
    Error err = ok;
    if (!src) { 
        CREATE_ERROR(err, ERROR_ARGS, "Cannot lex an empty source.");
        return err;
    }
    return ok;
}