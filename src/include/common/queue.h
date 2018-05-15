#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <common/memory.h>

typedef struct Queue queue_t;
typedef struct Link link_t;

/**
* Allocates space for a queue and returns an empty queue
*/
queue_t *queue_new();

/**
* Enqueues data to a queue
* @param [in] queue A queue
* @param [in] data The data to enqueue
*/
void enqueue(queue_t *queue, void *data);

/*
*	Puts data in a new link at the beginning of a queue
* @param [in] queue A queue
* @param [in] data The data to store
*/
void enqueue_first(queue_t *queue, void *data);

/**
* Removes the first element of a queue and returns it
* @param [in] queue A queue
* @param [out] The data element of the first link
*/
void *dequeue(queue_t *queue);

/**
* Gives the length of a queue
* @param [in] queue A queue
* @param [out] The length of the queue
*/
int list_size(queue_t *queue);

/*
* Returns the first element in the list
*/
void *get_first_element(queue_t *queue);

#endif
