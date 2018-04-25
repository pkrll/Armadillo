#include "common/malloc.h"



void malloc_init() {
  heap_t *start = (heap_t *)((uint32_t)&__end);
  start->next_allocation = ((uint32_t)&__end + METADATA);
}

void *malloc(size_t size) {
  heap_t *start = (heap_t *)((uint32_t)&__end);
  uint32_t allocation_adress = start->next_allocation;
  size_t pages_allocated = (size/PAGESIZE) + 1;
  size_t memory_allocated = pages_allocated * PAGESIZE;
  start->next_allocation += memory_allocated;
  return (void *)allocation_adress;
}
