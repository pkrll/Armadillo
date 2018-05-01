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

/*
*	Allocates space for a list, initiates the f irst and last pointers along with the list size.
* @param [out] A pointer to a list
*/
list_t *list_new(){
    list_t *list = malloc(sizeof(list_t*));
    list->first = link_new();
    list->last = link_new();
    list->size = 0;
    return list;
};

/*
*	Puts data in a new link at the end of a list
* @param [in] list A list
* @param [in] data The data to store
*/
void enqueue(list_t *list, void *data){
  link_t *new = link_new();
  new->data = data;

  new->next = NULL;
  if (list->last) {
    list->last->next = new;
  }

  if (list->size == 0) {
    list->first = new;
  }

  list->last = new;
  list->size++;

  if (list->size == 0) {
    list->last = new;
  }
};

/*
*	Removes the first link in a list and returns its data.
* @param [in] list A list
* @param [out]  Data member of the first link
*/
void *pop(list_t *list){
  void *result;
  if (list -> size>0) {
    result = list -> first->data;
    list->first = list->first->next;
    list->size--;
  }
  return result;
};

/*
*	Returns the size of a list
*/
int list_size(list_t *list){
  return list->size;
};
