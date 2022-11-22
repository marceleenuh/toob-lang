#pragma once
#include "error.h"
#include "Environment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Pretty much Lens_r's code
typedef struct Token {
    char* beginning;
    char* end;
    struct Token* next;
} Token;

Error lex(char* src, Token* token);
Error parseExpression(char* src, Node* result);
Token* createToken();
Token createLexableToken(char* src);