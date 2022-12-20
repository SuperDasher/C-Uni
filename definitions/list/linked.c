#include <list/linked.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct _node
{
	int data;
	struct _node *next;
} node;

typedef struct _linked_list
{
	node *head;
	node *tail;
} *linked_list;

typedef struct _linked_list_iterator
{
	linked_list list;
	node *current;
	int index;
} *linked_list_iterator;

typedef int (*compare_function)(int, int);

// Utility functions definitions not exposed in the header file
int compare(int a, int b);
int compare_desc(int a, int b);
void linked_list_quick_sort_helper(linked_list list, int low, int high, compare_function compare);
int linked_list_partition(linked_list list, int low, int high, compare_function compare);
void null_list_check(linked_list list);
void malloc_fail_check(void *ptr);
void index_out_of_range_check(linked_list list, int index);
void empty_list_check(linked_list list);
void linked_list_remove_node(linked_list list, node *node_to_remove);

linked_list_iterator linked_list_iterator_begin(linked_list list)
{
	linked_list_iterator iterator = malloc(sizeof(struct _linked_list_iterator));
	malloc_fail_check(iterator);
	iterator->list = list;
	iterator->current = list->head;
	iterator->index = 0;
	return iterator;
}

linked_list_iterator linked_list_iterator_copy(linked_list_iterator iterator)
{
	linked_list_iterator copy = malloc(sizeof(struct _linked_list_iterator));
	malloc_fail_check(copy);
	copy->list = iterator->list;
	copy->current = iterator->current;
	copy->index = iterator->index;
	return copy;
}

bool linked_list_iterator_has_next(linked_list_iterator iterator)
{
	return iterator->current->next != NULL;
}

void linked_list_iterator_next(linked_list_iterator iterator)
{
	if (!linked_list_iterator_has_next(iterator))
	{
		fprintf(stderr, "iterator has no next element\n");
		exit(EXIT_FAILURE);
	}
	iterator->current = iterator->current->next;
	iterator->index++;
}

bool linked_list_iterator_has_previous(linked_list_iterator iterator)
{
	return iterator->index != 0;
}

void linked_list_iterator_previous(linked_list_iterator iterator)
{
	if (iterator->index == 0)
	{
		fprintf(stderr, "iterator has no previous element\n");
		exit(EXIT_FAILURE);
	}
	linked_list_iterator temp = linked_list_iterator_begin(iterator->list);
	while (temp->index < iterator->index - 1)
	{
		linked_list_iterator_next(temp);
	}
	iterator->current = temp->current;
	iterator->index--;
	linked_list_iterator_destroy(temp);
}

int linked_list_iterator_index(linked_list_iterator iterator)
{
	return iterator->index;
}

int linked_list_iterator_data(linked_list_iterator iterator)
{
	return iterator->current->data;
}

void linked_list_iterator_set(linked_list_iterator iterator, int data)
{
	iterator->current->data = data;
}

void linked_list_iterator_insert(linked_list_iterator iterator, int data)
{
	node *new_node = malloc(sizeof(node));
	malloc_fail_check(new_node);
	new_node->data = data;
	new_node->next = iterator->current;
	if (iterator->index == 0)
	{
		iterator->list->head = new_node;
	}
	else
	{
		linked_list_iterator temp = linked_list_iterator_begin(iterator->list);
		while (temp->index < iterator->index - 1)
		{
			linked_list_iterator_next(temp);
		}
		temp->current->next = new_node;
		linked_list_iterator_destroy(temp);
	}
	iterator->index++;
}

void linked_list_iterator_remove(linked_list_iterator iterator)
{
	if (iterator->index == 0)
	{
		iterator->list->head = iterator->current->next;
	}
	else
	{
		linked_list_iterator temp = linked_list_iterator_begin(iterator->list);
		while (temp->index < iterator->index - 1)
		{
			linked_list_iterator_next(temp);
		}
		temp->current->next = iterator->current->next;
		linked_list_iterator_destroy(temp);
	}
	iterator->index--;
	linked_list_remove_node(iterator->list, iterator->current);
	iterator->current = iterator->current->next;
}

void linked_list_iterator_destroy(linked_list_iterator iterator)
{
	free(iterator);
}

linked_list linked_list_create()
{
	linked_list list = (linked_list)malloc(sizeof(struct _linked_list));
	malloc_fail_check((void *)list);
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void linked_list_destroy(linked_list *list)
{
	null_list_check(*list);
	if (list == NULL)
	{
		fprintf(stderr, "passed NULL pointer to linked_list_destroy\n");
		exit(EXIT_FAILURE);
	}
	node *current = (*list)->head;
	node *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(*list);
	*list = NULL;
}

void linked_list_scan(linked_list list, int n)
{
	null_list_check(list);
	int data;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &data);
		linked_list_insert(list, data);
	}
}

void linked_list_insert_head(linked_list list, int data)
{
	null_list_check(list);
	node *new_node = (node *)malloc(sizeof(node));
	malloc_fail_check((void *)new_node);
	new_node->data = data;
	new_node->next = list->head;
	list->head = new_node;
	if (list->tail == NULL)
	{
		list->tail = new_node;
	}
}

void linked_list_insert(linked_list list, int data)
{
	null_list_check(list);
	node *new_node = (node *)malloc(sizeof(node));
	malloc_fail_check((void *)new_node);
	new_node->data = data;
	new_node->next = NULL;
	if (list->tail == NULL)
	{
		list->head = new_node;
	}
	else
	{
		list->tail->next = new_node;
	}
	list->tail = new_node;
}

void linked_list_insert_at(linked_list list, int data, int index)
{
	null_list_check(list);
	if (index < 0 || index > linked_list_size(list))
	{
		fprintf(stderr, "Index out of range: %d\n", index);
		exit(EXIT_FAILURE);
	}

	if (index == 0)
	{
		linked_list_insert_head(list, data);
	}
	else if (index == linked_list_size(list))
	{
		linked_list_insert(list, data);
	}
	else
	{
		node *new_node = (node *)malloc(sizeof(node));
		malloc_fail_check((void *)new_node);
		new_node->data = data;
		node *current = list->head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void linked_list_insert_ordered(linked_list list, int data)
{
	null_list_check(list);
	if (linked_list_is_empty(list))
	{
		linked_list_insert(list, data);
		return;
	}
	if (!linked_list_is_sorted(list) && !linked_list_is_sorted_desc(list))
	{
		fprintf(stderr, "List is not sorted\n");
		exit(EXIT_FAILURE);
	}
	node *new_node = (node *)malloc(sizeof(node));
	malloc_fail_check((void *)new_node);
	new_node->data = data;
	node *current = list->head;
	node *previous = NULL;
	if (linked_list_is_sorted(list))
	{
		while (current != NULL && current->data < data)
		{
			previous = current;
			current = current->next;
		}
	}
	else
	{
		while (current != NULL && current->data > data)
		{
			previous = current;
			current = current->next;
		}
	}
	if (previous == NULL)
	{
		linked_list_insert_head(list, data);
	}
	else
	{
		new_node->next = current;
		previous->next = new_node;
		if (current == NULL)
		{
			list->tail = new_node;
		}
	}
}

void linked_list_remove_head(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	list->head = current->next;
	free(current);
}

void linked_list_remove_tail(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	while (current->next != list->tail)
	{
		current = current->next;
	}
	free(list->tail);
	list->tail = current;
	list->tail->next = NULL;
}

void linked_list_remove_at(linked_list list, int index)
{
	null_list_check(list);
	empty_list_check(list);
	index_out_of_range_check(list, index);

	if (index == 0)
	{
		linked_list_remove_head(list);
	}
	else if (index == linked_list_size(list) - 1)
	{
		linked_list_remove_tail(list);
	}
	else
	{
		node *current = list->head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}
		node *temp = current->next;
		current->next = temp->next;
		free(temp);
	}
}

int linked_list_size(linked_list list)
{
	null_list_check(list);
	int size = 0;
	node *current = list->head;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return size;
}

bool linked_list_is_empty(linked_list list)
{
	null_list_check(list);
	return list->head == NULL;
}

int linked_list_get_head(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	return list->head->data;
}

int linked_list_get_tail(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	return list->tail->data;
}

int linked_list_get(linked_list list, int index)
{
	null_list_check(list);
	empty_list_check(list);
	index_out_of_range_check(list, index);
	node *current = list->head;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->data;
}

void linked_list_set_head(linked_list list, int data)
{
	null_list_check(list);
	empty_list_check(list);
	list->head->data = data;
}

void linked_list_set_tail(linked_list list, int data)
{
	null_list_check(list);
	empty_list_check(list);
	list->tail->data = data;
}

void linked_list_set(linked_list list, int data, int index)
{
	null_list_check(list);
	empty_list_check(list);
	index_out_of_range_check(list, index);
	node *current = list->head;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}
	current->data = data;
}

void linked_list_print(linked_list list)
{
	null_list_check(list);
	node *current = list->head;
	if (current == NULL)
	{
		printf("list is empty\n");
		return;
	}
	while (current != list->tail)
	{
		printf("%d --> ", current->data);
		current = current->next;
	}
	printf("%d\n", current->data);
}

linked_list linked_list_copy(linked_list list)
{
	null_list_check(list);
	linked_list new_list = linked_list_create();
	node *current = list->head;
	for (int i = 0; i < linked_list_size(list); i++)
	{
		linked_list_insert(new_list, current->data);
		current = current->next;
	}
	return new_list;
}

void linked_list_rotate_left(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = list->head;
	list->head = list->head->next;
	current->next->next = NULL;
	list->tail = current->next;
}

void linked_list_rotate_right(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	while (current->next != list->tail)
	{
		current = current->next;
	}
	current->next = NULL;
	list->tail->next = list->head;
	list->head = list->tail;
	list->tail = current;
}

void linked_list_reverse(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	node *prev = NULL;
	node *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	list->tail = list->head;
	list->head = prev;
}

void linked_list_clear(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	node *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
}

void linked_list_swap(linked_list list, int index1, int index2)
{
	int temp = linked_list_get(list, index1);
	linked_list_set(list, linked_list_get(list, index2), index1);
	linked_list_set(list, temp, index2);
}

void linked_list_sort(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	linked_list_quick_sort_helper(list, 0, linked_list_size(list) - 1, compare);
}

void linked_list_sort_desc(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	linked_list_quick_sort_helper(list, 0, linked_list_size(list) - 1, compare_desc);
}

int linked_list_min(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	int min = linked_list_get(list, 0);
	for (int i = 1; i < linked_list_size(list); i++)
	{
		if (linked_list_get(list, i) < min)
		{
			min = linked_list_get(list, i);
		}
	}
	return min;
}

int linked_list_max(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	int max = linked_list_get(list, 0);
	for (int i = 1; i < linked_list_size(list); i++)
	{
		if (linked_list_get(list, i) > max)
		{
			max = linked_list_get(list, i);
		}
	}
	return max;
}

int linked_list_sum(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	int sum = 0;
	for (int i = 0; i < linked_list_size(list); i++)
	{
		sum += linked_list_get(list, i);
	}
	return sum;
}

float linked_list_average(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	// deepcode ignore DivisionByZero: empty_list_check() will catch this
	return (float)linked_list_sum(list) / linked_list_size(list);
}

int *linked_list_to_array(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	int *array = malloc(sizeof(int) * linked_list_size(list));
	malloc_fail_check((void *)array);
	node *current = list->head;
	for (int i = 0; i < linked_list_size(list); i++)
	{
		array[i] = current->data;
		current = current->next;
	}
	return array;
}

linked_list linked_list_from_array(int *array, int size)
{
	if (array == NULL)
	{
		fprintf(stderr, "array is NULL");
		exit(EXIT_FAILURE);
	}
	linked_list list = linked_list_create();
	for (int i = 0; i < size; i++)
	{
		linked_list_insert(list, array[i]);
	}
	return list;
}

void linked_list_concatenate(linked_list dest, linked_list src)
{
	null_list_check(dest);
	null_list_check(src);
	empty_list_check(src);
	node *current = src->head;
	while (current != NULL)
	{
		linked_list_insert(dest, current->data);
		current = current->next;
	}
}

bool linked_list_contains_duplicates(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	node *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			if (next->data == current->data)
			{
				return true;
			}
			next = next->next;
		}
		current = current->next;
	}
	return false;
}

void linked_list_remove_duplicates(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	node *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			if (next->data == current->data)
			{
				node *temp = next;
				next = next->next;
				linked_list_remove_node(list, temp);
			}
			else
			{
				next = next->next;
			}
		}
		current = current->next;
	}
}

bool linked_list_contains(linked_list list, int data)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	while (current != NULL)
	{
		if (current->data == data)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

int linked_list_occurrences_of(linked_list list, int data)
{
	null_list_check(list);
	empty_list_check(list);
	int count = 0;
	node *current = list->head;
	while (current != NULL)
	{
		if (current->data == data)
		{
			count++;
		}
		current = current->next;
	}
	return count;
}

int *linked_list_indices_of(linked_list list, int data)
{
	null_list_check(list);
	empty_list_check(list);
	int malloc_size = sizeof(int) * linked_list_occurrences_of(list, data);
	if (malloc_size == 0)
		return NULL;
	int *indices = malloc(malloc_size);
	malloc_fail_check((void *)indices);
	int count = 0;
	node *current = list->head;
	for (int i = 0; i < linked_list_size(list); i++)
	{
		if (current->data == data)
			indices[count++] = i;
		current = current->next;
	}
	return indices;
}

int linked_list_first_index_of(linked_list list, int data)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	for (int i = 0; i < linked_list_size(list); i++)
	{
		if (current->data == data)
			return i;
		current = current->next;
	}
	return -1;
}

int linked_list_last_index_of(linked_list list, int data)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	int index = -1;
	for (int i = 0; i < linked_list_size(list); i++)
	{
		if (current->data == data)
			index = i;
		current = current->next;
	}
	return index;
}

int linked_list_index_of(linked_list list, int data, int occurrence)
{
	null_list_check(list);
	empty_list_check(list);
	index_out_of_range_check(list, occurrence);
	node *current = list->head;
	int count = 0;
	for (int i = 0; i < linked_list_size(list); i++)
	{
		if (current->data == data)
		{
			if (count == occurrence)
				return i;
			count++;
		}
		current = current->next;
	}
	return -1;
}

void linked_list_remove(linked_list list, int data)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	while (current != NULL)
	{
		if (current->data == data)
		{
			node *temp = current;
			current = current->next;
			linked_list_remove_node(list, temp);
		}
		else
		{
			current = current->next;
		}
	}
}

bool linked_list_equals(linked_list list1, linked_list list2)
{
	null_list_check(list1);
	null_list_check(list2);
	if (linked_list_size(list1) != linked_list_size(list2))
		return false;
	node *current1 = list1->head;
	node *current2 = list2->head;
	while (current1 != NULL)
	{
		if (current1->data != current2->data)
			return false;
		current1 = current1->next;
		current2 = current2->next;
	}
	return true;
}

bool linked_list_is_sorted(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	while (current->next != NULL)
	{
		if (current->data > current->next->data)
			return false;
		current = current->next;
	}
	return true;
}

bool linked_list_is_sorted_desc(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	node *current = list->head;
	while (current->next != NULL)
	{
		if (current->data < current->next->data)
			return false;
		current = current->next;
	}
	return true;
}

/*******************************/
/****** Private functions ******/
/*******************************/

// normal compare function for linked_list_sort
int compare(int a, int b)
{
	return a - b;
}

// reverse compare function for linked_list_sort_reverse
int compare_desc(int a, int b)
{
	return b - a;
}

// Helper function for linked_list_sort
void linked_list_quick_sort_helper(linked_list list, int low, int high, compare_function compare)
{
	if (low < high)
	{
		int pi = linked_list_partition(list, low, high, compare);
		linked_list_quick_sort_helper(list, low, pi - 1, compare);
		linked_list_quick_sort_helper(list, pi + 1, high, compare);
	}
}

int linked_list_partition(linked_list list, int low, int high, compare_function compare)
{
	int pivot = linked_list_get(list, high);
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (compare(linked_list_get(list, j), pivot) < 0)
		{
			i++;
			linked_list_swap(list, i, j);
		}
	}
	linked_list_swap(list, i + 1, high);
	return i + 1;
}

// Other helper functions
void null_list_check(linked_list list)
{
	if (list == NULL)
	{
		fprintf(stderr, "list is NULL\n");
		exit(EXIT_FAILURE);
	}
}

void malloc_fail_check(void *ptr)
{
	if (ptr == NULL)
	{
		perror("malloc() failed");
		exit(errno);
	}
}

void index_out_of_range_check(linked_list list, int index)
{
	if (index < 0 || index >= linked_list_size(list))
	{
		fprintf(stderr, "index out of range\n");
		exit(EXIT_FAILURE);
	}
}

void empty_list_check(linked_list list)
{
	if (linked_list_is_empty(list))
	{
		fprintf(stderr, "list is empty\n");
		exit(EXIT_FAILURE);
	}
}

void linked_list_remove_node(linked_list list, node *node_to_remove)
{
	if (node_to_remove == list->head)
	{
		list->head = node_to_remove->next;
	}
	else
	{
		node *current = list->head;
		while (current->next != node_to_remove)
		{
			current = current->next;
		}
		current->next = node_to_remove->next;
		if (node_to_remove == list->tail)
		{
			list->tail = current;
		}
	}
	free(node_to_remove);
}

// file deepcode ignore DerefOfMaybeNull: malloc_fail_check is used
// file deepcode ignore CMemoryLeak: the memory is freed in linked_list_destroy
