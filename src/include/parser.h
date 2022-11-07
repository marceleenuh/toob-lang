#pragma once
#include "error.h"
#include <stdio.h>
#include <string.h>

// Pretty much Lens_r's code
Error lex(char* src, char** beg, char** end);
Error parseExpression(char* src);