#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stddef.h>
#include <common/stdint.h>

extern uint8_t __end __attribute__((section (".data")));
#define METADATA 0x2000
#define PAGESIZE 0X1000

typedef struct Heap {
  uint32_t next_allocation;
}heap_t;

void *malloc(size_t size);
void malloc_init();

#endif
