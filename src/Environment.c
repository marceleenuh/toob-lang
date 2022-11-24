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