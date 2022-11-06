#include "include/lexer.h"

#include <stdio.h>
#include <stdlib.h>

void printUsage(char** argv) {
    printf("Usage: %s <path_to_target_file>\n", argv[0]);
}

long fileSize(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

char* fileContents(char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Error while opening %s\n", path);
        return NULL;
    }

    long size = fileSize(file);
    if (size == 0) {
        return NULL;
    }

    char* contents = malloc(size + 1);
    size_t bytesRead = fread(contents, 1, size, file);
    if (bytesRead != size) {
        free(contents);
        return NULL;
    }

    // Make sure to null-terminate the file contents so that we don't get any string-related issues.
    contents[size] = '\0';
    return contents;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printUsage(argv);
        exit(0);
    }

    char* filepath = argv[1];
    char* contents = fileContents(filepath);
    lex(contents);
}