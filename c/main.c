#include <stdio.h>
#include "dllist.h"

int main(void) {
    printf("Hello, world!\n");

    Node* list = NULL;

    insert(&list, NULL, "five");
    insert(&list, NULL, "one");
    insert(&list, find(list, "one"), "two");
    insert(&list, find(list, "two"), "three");
    insert(&list, find(list, "three"), "four");


    dump(list);

    printf("-- delete two --\n");
    delete(&list, find(list, "two"));
    dump(list);

    printf("-- delete four --\n");
    delete(&list, find(list, "four"));
    dump(list);


    return 0;
}