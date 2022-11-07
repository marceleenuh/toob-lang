#include "error.h"

void printError(Error err) {
    if (err.type == ERROR_NONE) { return; }
    switch (err.type) {
        case ERROR_TYPE:
            printf("[TYPE ERROR] %s", err.msg);
            break;
        case ERROR_ARGS:
            printf("[ARGUMENT ERROR] %s", err.msg);
            break;
        case ERROR_SYNTAX:
            printf("[SYNTAX ERROR] %s", err.msg);
            break;
        case ERROR_GENERIC:
            printf("[ERROR] %s", err.msg);
            break;
        default:
            printf("[ERROR] Unknown Error.");
            break;
    }
    putchar('\n');
}