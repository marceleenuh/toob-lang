#pragma once

typedef long long toobInt;
typedef struct Node {
    enum NodeType {
        NODE_TYPE_NONE = 0,
		NODE_TYPE_ROOT,
        NODE_TYPE_INT,
    } type;
    union NodeValue {
		toobInt toobInt;
    } value;

	struct Node** children;
} Node;

#define noneNode (node) ((node).type == NODE_TYPE_NONE)
#define rootNode (node) ((node).type == NODE_TYPE_ROOT)
#define intNode (node) ((node).type == NODE_TYPE_INT)

typedef struct Binding {
    char* id;
    Node* value;
    struct Binding* next;
} Binding;

typedef struct Scope {
    struct Scope* parent;
} Scope;

void setScope();