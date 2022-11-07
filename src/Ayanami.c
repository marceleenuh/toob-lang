#include "parser.h"
#include "error.h"
#include "fileIO.h"

#include <stdio.h>
#include <stdlib.h>

void printUsage(char** argv) {
    printf("Usage: %s <path_to_target_file>\n", argv[0]);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printUsage(argv);
        exit(0);
    }

    char* filepath = argv[1];
    char* contents = fileContents(filepath);

    Error err = parseExpression(contents);
    printError(err);
}