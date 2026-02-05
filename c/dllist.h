#ifndef DLLIST_H
#define DLLIST_H

typedef struct Node {
    char *value;
    struct Node *prev;
    struct Node *next;
} Node;

Node* find(Node* list, const char* value);
void insert(Node** list, Node* after, const char* value);
void delete(Node** list, Node* node);
void dump(Node* list);

#endif
