#include <stdio.h>
#include <stdlib.h>

char* fileContents(char* path) {
    FILE* file = fopen(path, "r");
}

void printUsage(char** argv) {
    printf("Usage: %s <path_to_target_file>\n", argv[0]);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printUsage(argv);
        exit(0);
    }
    printf("Rei Says hi!\n");
}