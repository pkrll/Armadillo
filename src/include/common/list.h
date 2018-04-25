#ifndef _LIST_H_
#define _LIST_H_

#include "common/malloc.h"

typedef struct list list_t;
typedef struct link link_t;

list_t *list_new();
void enqueue(list_t *list, void *data);
void *pop(list_t *list);
int list_size(list_t *list);

#endif
