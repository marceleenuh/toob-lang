#include "Environment.h"

Node* createNode() {
    Node* node = calloc(1, sizeof(Node));
    assert(node && "Couldn't allocate memory for node");
    return node;
}