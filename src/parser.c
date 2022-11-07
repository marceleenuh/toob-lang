#include "parser.h"

Error ok = { ERROR_NONE, "ok"};

// Thanks Lens_r
const char* whitespace = " ;\r\n";
const char* delimiters = ";\r";

Error lex(char* src, char** beg, char** end) {
    Error err = ok;
    if (!src || !beg || !end) { 
        CREATE_ERROR(err, ERROR_ARGS, "Cannot lex an empty source.");
        return err;
    }
    *beg = src;
    *beg += strspn(*beg, whitespace);
    *end = *beg;
    *end += strcspn(*beg, delimiters);
    return ok;
}

Error parseExpression(char* src) {
    char* beg = src;
    char* end = src;
    Error err = ok;
    while ((err = lex(end, &beg, &end)).type == ERROR_NONE) {
        if (end - beg == 0) { break; }
        printf("Lexed: %.*s\n", end - beg, beg);
    }
    return err;
}