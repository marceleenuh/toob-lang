#include "include/lexer.h"

#include <stdio.h>

Error ok = { ERROR_NONE, "ok"};

Error lex(char* contents, char** result) {
    printf("%s\n", contents);
    return ok;
}