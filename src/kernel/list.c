#include <common/list.h>

/**
* Struct used as links in a list. Contains a pointer to
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
struct List{
  link_t *first;
  link_t *last;
  int size;
};

/**
* Allocates space for a link, initiates data and next to NULL.
* @param [out] Pointer to the link
*/
link_t *link_new(){
  link_t *link = malloc(sizeof(link_t*));
  link->data = NULL;
  link->next = NULL;
  return link;
};

list_t *list_new(){
    list_t *list = malloc(sizeof(list_t*));
    list->first = link_new();
    list->last = link_new();
    list->size = 0;
    return list;
};

void enqueue(list_t *list, void *data){
  link_t *new = link_new();
  new->data = data;

  new->next = list->first;
  list->first = new;
  list->size++;

  if (list->size == 0) {
    list->last = new;
  }
};

void *pop(list_t *list){
  void *result;
  if (list -> size>0) {
    result = list -> first->data;
    list->first = list->first->next;
    list->size--;
  }
  return result;
};

int list_size(list_t *list);
