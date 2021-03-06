/**
 * @file
 * @brief Queue data structure
 */

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <common/memory.h>

typedef struct Queue queue_t;
typedef struct Link link_t;

/**
* Allocates space for a queue and returns an empty queue
*/
/**
 * Creates a new queue data structure.
 *
 * @return A pointer to a new, empty queue.
 */
queue_t *queue_new();
/**
 * Pushes data to the end of the queue.
 *
 * @param queue A queue.
 * @param data  The data to enqueue.
 */
void enqueue(queue_t *queue, void *data);
/**
 * Returns the first element of a queue.
 *
 * @param  queue A queue
 * @return The element at the front.
 */
void *queue_front(queue_t *queue);
/**
 * Removes the first element of a queue, and returns it.
 *
 * @param  queue A queue.
 * @return The data element at the head of the queue.
 */
void *dequeue(queue_t *queue);
/**
 * Deallocates a queue.
 *
 * @param queue The queue to deallocate.
 */
void queue_destroy(queue_t *queue);
/**
 * Gives the length of a queue.
 *
 * @param  queue A queue.
 * @return The length of a queue.
 */
int list_size(queue_t *queue);

/*
* Returns the first element in the list
*/
void *get_first_element(queue_t *queue);

#endif
