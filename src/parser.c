#include "parser.h"

Error ok = { ERROR_NONE, "ok"};

// Thanks Lens_r
const char* whitespace = " \r";
const char* delimiters = ";";

Error lex(char* src, char** beg, char** end) {
    Error err = ok;
    if (!src || !beg || !end) { 
        CREATE_ERROR(err, ERROR_ARGS, "Cannot lex an empty source.");
        return err;
    }
    *beg = src;
    *end = src;
    return ok;
}

Error parseExpression(char* src) {
    char* beg = src;
    char* end = src;
    Error err = lex(src, &beg, &end);
    
    return err;
}