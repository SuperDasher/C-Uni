#include <stdbool.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _linked_list *linked_list;

linked_list linked_list_create();

void linked_list_destroy(linked_list *list);

void linked_list_add_head(linked_list list, int data);

void linked_list_add_tail(linked_list list, int data);

void linked_list_add_at(linked_list list, int data, int index);

void linked_list_remove_head(linked_list list);

void linked_list_remove_tail(linked_list list);

void linked_list_remove_at(linked_list list, int index);

int linked_list_size(linked_list list);

bool linked_list_is_empty(linked_list list);

int linked_list_get_head(linked_list list);

int linked_list_get_tail(linked_list list);

int linked_list_get(linked_list list, int index);

void linked_list_set_head(linked_list list, int data);

void linked_list_set_tail(linked_list list, int data);

void linked_list_set(linked_list list, int data, int index);

void linked_list_print(linked_list list);

linked_list linked_list_copy(linked_list list);

void linked_list_reverse(linked_list list);

void linked_list_clear(linked_list list);

void linked_list_swap(linked_list list, int index1, int index2);

void linked_list_sort(linked_list list);

void linked_list_sort_desc(linked_list list);

#endif /* LINKED_LIST_H */