#include "common/list.h"

struct link{
  void *data;
  link_t *next;
};

struct list{
  link_t *first;
  link_t *last;
  int size;
};

link_t *link_new(){
  link_t *link = malloc(sizeof(link_t*));
  return link;
}

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
  if (list->size>0) {
    result = list->first->data;
    list->first = list->first->next;
    list->size--;
  }
  return result;
};
int list_size(list_t *list);
