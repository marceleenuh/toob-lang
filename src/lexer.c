#include "include/lexer.h"

#include <stdio.h>

Error ok = { ERROR_NONE, "ok"};

Error lex(char* contents) {
    printf("%s\n", contents);
    return ok;
}