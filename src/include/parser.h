#pragma once
#include "error.h"
#include <stdio.h>
#include <string.h>

// Thanks Lens_r
Error lex(char* src, char** beg, char** end);
Error parseExpression(char* src);