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

	if (queue) {
		queue->first = NULL;
		queue->last = NULL;
		queue->size = 0;
	}

	return queue;
}

void enqueue_first(queue_t *queue, void *data) {
	link_t *new = link_new();
	new->data = data;

	new->next = NULL;
	if (queue->first) {
		new->next = queue->first;
	}

	if (queue->size == 0) {
		queue->last = new;
	}
	queue->first = new;
	queue->size++;
}

void enqueue(queue_t *queue, void *data) {
	link_t *link = link_new();

	if (link) {
		if (queue->size == 0) {
			queue->first = link;
		} else {
			queue->last->next = link;
		}

		link->data = data;
		link->next = queue->last;

		queue->last = link;
		queue->size++;
	}
}

void *dequeue(queue_t *queue) {
	void *data = NULL;

	if (queue && queue->size > 0) {
		link_t *link = queue->first;
		data = link->data;

		queue->first = link->next;
		queue->size--;

		free(link);
	}

	return data;
}

void queue_destroy(queue_t *queue) {
	if (queue == NULL) return;

	link_t *current = queue->first;

	while (current) {
		link_t *link = current;
		current = link->next;
		free(link);
	}

	free(queue);
}

int list_size(queue_t *queue) {
	return (queue) ? queue->size : 0;
}

// -------------------------------
// Internal functions
// -------------------------------

link_t *link_new() {
	link_t *link = malloc(sizeof(link_t));

	if (link) {
		link->data = NULL;
		link->next = NULL;
	}

	return link;
}
