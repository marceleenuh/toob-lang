#include "parser.h"
#include "error.h"
#include "fileIO.h"
#include "Environment.h"

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
    if (!contents)
        exit(-1);

    Error err = parseExpression(contents, NULL);
    printError(err);

    free(contents);
}