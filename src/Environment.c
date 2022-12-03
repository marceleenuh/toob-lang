#include "Environment.h"

Node* createNode() {
    Node* node = calloc(1, sizeof(Node));
    assert(node && "Couldn't allocate memory for node");
    return node;
}

size_t freeNode(Node* node) {
    // Completely copied from lens_r
    if (!node) { return 0; }
    size_t count = 1;
    Node* child = node->children;
    Node* next = NULL;
    while (child) {
        next = child->nextChild;
        freeNode(child);
        child = next;
        count++;
    }

    free(node);
    return count;
}

char* generateUUID() {
    char v[] = "0123456789abcdef";
    static char buf[37] = {0};

    for(int i = 0; i < 36; ++i) {
        buf[i] = v[rand()%16];
    }

    buf[8] = '-';
    buf[13] = '-';
    buf[18] = '-';
    buf[23] = '-';

    buf[36] = '\0';

    return buf;
}

char* s_generateUUID(uint32_t seed) {
    char v[] = "0123456789abcdef";
    static char buf[37] = {0};

    for(int i = 0; i < 36; i++) {
        srand(seed+i);
        buf[i] = v[rand()%16];
    }

    buf[8] = '-';
    buf[13] = '-';
    buf[18] = '-';
    buf[23] = '-';

    buf[36] = '\0';

    return buf;
}