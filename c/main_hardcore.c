#include <stdio.h>
#include <string.h>

#include "memory_hardcore.h"

int main(void) {
  if (!hardcore_allocator_init(1024)) {
    fprintf(stderr, "Could not start hardcore allocator.\n");
    return 1;
  }

  char* first = (char*)hardcore_reallocate(NULL, 0, 16);
  strcpy(first, "Hello");

  char* second = (char*)hardcore_reallocate(NULL, 0, 16);
  strcpy(second, "World");

  printf("First block: %s\n", first);
  printf("Second block: %s\n", second);

  char* bigger = (char*)hardcore_reallocate(first, 16, 32);
  strcat(bigger, " allocator");

  printf("Resized block: %s\n", bigger);

  hardcore_reallocate(second, 16, 0);
  hardcore_reallocate(bigger, 32, 0);

  hardcore_allocator_shutdown();

  return 0;
}