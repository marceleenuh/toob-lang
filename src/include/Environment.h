#pragma once
#include <assert.h>
#include <stdlib.h>

typedef long long tInt;
typedef struct Node {
    enum NodeType {
        NODE_TYPE_NONE = 0,
		NODE_TYPE_ROOT,
        NODE_TYPE_INT,
    } type;
    union NodeValue {
		tInt tInt;
    } value;

	struct Node** children;
} Node;

#define nodeNone (node) ((node).type == NODE_TYPE_NONE)
#define nodeRoot (node) ((node).type == NODE_TYPE_ROOT)
#define nodeInt (node) ((node).type == NODE_TYPE_INT)

typedef struct Binding {
    char* id;
    Node* value;
    struct Binding* next;
} Binding;

typedef struct Scope {
    struct Scope* parent;
} Scope;

void setScope();
Node* createNode();