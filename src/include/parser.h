#pragma once
#include "error.h"
#include <stdio.h>

// Thanks Lens_r
Error lex(char* src, char** beg, char** end);
Error parseExpression(char* src);