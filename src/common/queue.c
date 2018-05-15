#include <common/queue.h>

/**
* Struct used as links in a queue. Contains a pointer to
* data and a pointer to the next item in the list, if any.
*/
struct Link{
  void *data;
  link_t *next;
};

/**
* List struct with pointers to the first and last element
* and also the size of the list.
*/
struct Queue{
  link_t *first;
  link_t *last;
  int size;
};

/**
* Allocates space for a link, initiates data and next to NULL.
* @param [out] Pointer to the link
*/
link_t *link_new(){
  link_t *link = malloc(sizeof(link_t));
  link->data = NULL;
  link->next = NULL;
  return link;
};

/*
*	Allocates space for a queue, initiates the f irst and last pointers along with the queue size.
* @param [out] A pointer to a queue
*/
queue_t *queue_new(){
    queue_t *queue = malloc(sizeof(queue_t));
    queue->first = link_new();
    queue->last = link_new();
    queue->size = 0;
    return queue;
};

/*
*	Puts data in a new link at the end of a queue
* @param [in] queue A queue
* @param [in] data The data to store
*/
void enqueue(queue_t *queue, void *data){
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
};

/*
*	Puts data in a new link at the beginning of a queue
* @param [in] queue A queue
* @param [in] data The data to store
*/
void enqueue_first(queue_t *queue, void *data){
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

/*
*	Removes the first link in a queue and returns its data.
* @param [in] queue A queue
* @param [out]  Data member of the first link
*/
void *dequeue(queue_t *queue){
  void *result = NULL;
  if (queue && queue -> size > 0) {
    link_t *temp = queue->first;
    result = temp->data;
    queue->first = temp->next;
    //free(temp);
    queue->size--;
  }
  return result;
};

/*
*	Returns the size of a queue
*/
int list_size(queue_t *queue){
  return queue->size;
};

/*
* Returns the first element in the list
*/
void *get_first_element(queue_t *queue) {
  return queue->first->data;
}
