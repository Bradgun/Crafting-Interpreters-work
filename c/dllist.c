#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Make a heap copy of a C-string
static char* str_dup(const char* s) {
    char* copy = (char*)malloc(strlen(s) + 1);
    if (copy) strcpy(copy, s);
    return copy;
}

Node* find(Node* list, const char* value) {
    while (list != NULL) {
        if (strcmp(list->value, value) == 0) {
            return list;
        }
        list = list->next;
    }
    return NULL;
}

void insert(Node** list, Node* after, const char* value) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return;

    n->value = str_dup(value);
    if (!n->value) {
        free(n);
        return;
    }

    // Insert at front if after == NULL
    if (after == NULL) {
        n->prev = NULL;
        n->next = *list;

        if (*list != NULL) {
            (*list)->prev = n;
        }

        *list = n;
        return;
    }

    // Insert after a  node
    n->prev = after;
    n->next = after->next;

    if (after->next != NULL) {
        after->next->prev = n;
    }

    after->next = n;
}

void delete(Node** list, Node* node) {
    if (node == NULL) return;

    if (node->prev == NULL) {
        *list = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    free(node->value);
    free(node);
}

void dump(Node* list) {
    while (list != NULL) {
        printf("%s ", list->value);
        list = list->next;
    }
    printf("\n");
}
