#include <common/queue.h>

// -------------------------------
// Structs
// -------------------------------

/**
 * Struct used as links in a queue. Contains a pointer to
 * data and a pointer to the next item in the list, if any.
 */
struct Link {
	void *data;
	link_t *next;
};

/**
 * List struct with pointers to the first and last element
 * and also the size of the list.
 */
struct Queue {
	link_t *first;
	link_t *last;
	int size;
};

// -------------------------------
// Declarations
// -------------------------------

/**
 * Allocates space for a link, initiates data and next to NULL.
 *
 * @return Pointer to the link
 */
link_t *link_new();

// -------------------------------
// Public functions
// -------------------------------

queue_t *queue_new() {
	queue_t *queue = malloc(sizeof(queue_t));
	queue->first = link_new();
	queue->last = link_new();
	queue->size = 0;
	return queue;
}

void enqueue(queue_t *queue, void *data) {
	link_t *new = link_new();
	new->data = data;

	new->next = NULL;
	if (queue->last) {
		queue->last->next = new;
	}

	if (queue->size == 0) {
		queue->first = new;
	}

	queue->last = new;
	queue->size++;
}

void *dequeue(queue_t *queue) {
	void *result = NULL;
	if (queue && queue -> size > 0) {
		link_t *temp = queue->first;
		result = temp->data;
		queue->first = temp->next;
		//free(temp);
		queue->size--;
	}
	return result;
}

int list_size(queue_t *queue) {
	return queue->size;
}

// -------------------------------
// Internal functions
// -------------------------------

link_t *link_new() {
	link_t *link = malloc(sizeof(link_t));
	link->data = NULL;
	link->next = NULL;
	return link;
};
