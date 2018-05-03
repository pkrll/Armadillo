<<<<<<< HEAD
#ifndef __QUEUE_H_
#define __QUEUE_H_
=======
#ifndef _QUEUE_H_
#define _QUEUE_H_
>>>>>>> 0353ca64ca879c9054387c1ca19f2f45faff88f0

#include <common/malloc.h>

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

#endif
