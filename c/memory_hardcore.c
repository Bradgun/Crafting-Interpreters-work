#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_hardcore.h"

static uint8_t* heap = NULL;
static size_t heapSize = 0;
static size_t heapUsed = 0;

bool hardcore_allocator_init(size_t heapBytes) {
  heap = (uint8_t*)malloc(heapBytes);
  if (heap == NULL) return false;

  heapSize = heapBytes;
  heapUsed = 0;
  return true;
}

void hardcore_allocator_shutdown(void) {
  free(heap);
  heap = NULL;
  heapSize = 0;
  heapUsed = 0;
}

static size_t alignSize(size_t size) {
  size_t alignment = sizeof(void*);
  return (size + alignment - 1) & ~(alignment - 1);
}

void* hardcore_reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    return NULL;
  }

  newSize = alignSize(newSize);

  if (heapUsed + newSize > heapSize) {
    fprintf(stderr, "Hardcore allocator ran out of memory.\n");
    return NULL;
  }

  void* newBlock = heap + heapUsed;
  heapUsed += newSize;

  if (pointer != NULL) {
    size_t bytesToCopy = oldSize < newSize ? oldSize : newSize;
    memcpy(newBlock, pointer, bytesToCopy);
  }

  return newBlock;
}