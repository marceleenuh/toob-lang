#pragma once
#include "error.h"
#include <stdio.h>
#include <string.h>

// Pretty much Lens_r's code
typedef struct Token {
    char* beginning;
    char* end;
    struct Token* next;
} Token;

Error lex(char* src, Token* token);
Error parseExpression(char* src);
Token createLexableToken(char* src);