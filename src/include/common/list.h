#ifndef _LIST_H_
#define _LIST_H_

#include <common/malloc.h>

typedef struct List list_t;
typedef struct Link link_t;

/**
* Allocates space for a list and returns an empty list
*/
list_t *list_new();

/**
* Enqueues data to a queue
* @param [in] list A list
* @param [in] data The data to enqueue
*/
void enqueue(list_t *list, void *data);

/**
* Removes the first element of a list and returns it
* @param [in] list A list
* @param [out] The data element of the first link
*/
void *pop(list_t *list);

/**
* Gives the length of a list
* @param [in] list A list
* @param [out] The length of the list
*/
int list_size(list_t *list);

#endif
