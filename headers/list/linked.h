#include <stdbool.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _linked_list *linked_list;

typedef struct _linked_list_iterator *linked_list_iterator;

linked_list_iterator linked_list_iterator_begin(linked_list list);

bool linked_list_iterator_has_next(linked_list_iterator iterator);

int linked_list_iterator_next(linked_list_iterator iterator);

bool linked_list_iterator_has_previous(linked_list_iterator iterator);

int linked_list_iterator_previous(linked_list_iterator iterator);

int linked_list_iterator_index(linked_list_iterator iterator);

int linked_list_iterator_data(linked_list_iterator iterator);

void linked_list_iterator_set(linked_list_iterator iterator, int data);

void linked_list_iterator_insert(linked_list_iterator iterator, int data);

void linked_list_iterator_remove(linked_list_iterator iterator);

void linked_list_iterator_destroy(linked_list_iterator iterator);

linked_list linked_list_create();

void linked_list_destroy(linked_list *list);

void linked_list_insert_head(linked_list list, int data);

void linked_list_insert(linked_list list, int data);

void linked_list_insert_at(linked_list list, int data, int index);

void linked_list_remove_head(linked_list list);

void linked_list_remove_tail(linked_list list);

void linked_list_remove_at(linked_list list, int index);

void linked_list_remove_data(linked_list list, int data);

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

int *linked_list_to_array(linked_list list);

linked_list linked_list_from_array(int *array, int size);

void linked_list_concatenate(linked_list dest, linked_list src);

bool linked_list_contains_duplicates(linked_list list);

void linked_list_remove_duplicates(linked_list list);

bool linked_list_contains(linked_list list, int data);

int linked_list_occurrences_of(linked_list list, int data);

int *linked_list_indices_of(linked_list list, int data);

int linked_list_first_index_of(linked_list list, int data);

int linked_list_last_index_of(linked_list list, int data);

int linked_list_index_of(linked_list list, int data, int offset);

void linked_list_remove(linked_list list, int data);

bool linked_list_equals(linked_list list1, linked_list list2);

bool linked_list_is_sorted(linked_list list);

bool linked_list_is_sorted_desc(linked_list list);

#endif /* LINKED_LIST_H */