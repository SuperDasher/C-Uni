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
} * linked_list;

// Utility functions definitions not exposed in the header file
void linked_list_quick_sort_helper(linked_list list, int low, int high);
int linked_list_partition(linked_list list, int low, int high);
void linked_list_swap(linked_list list, int index1, int index2);
void null_list_check(linked_list list);
void malloc_fail_check(void *ptr);
void index_out_of_range_check(linked_list list, int index);
void empty_list_check(linked_list list);

linked_list linked_list_create()
{
	linked_list list = (linked_list)malloc(sizeof(linked_list));
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

void linked_list_add_head(linked_list list, int data)
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

void linked_list_add_tail(linked_list list, int data)
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

void linked_list_add_at(linked_list list, int data, int index)
{
	null_list_check(list);
	if (index < 0 || index > linked_list_size(list))
	{
		fprintf(stderr, "Index out of range: %d\n", index);
		exit(EXIT_FAILURE);
	}

	if (index == 0)
	{
		linked_list_add_head(list, data);
	}
	else if (index == linked_list_size(list))
	{
		linked_list_add_tail(list, data);
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
	printf("[");
	while (current != list->tail)
	{
		printf("%d, ", current->data);
		current = current->next;
	}
	printf("%d]\n", current->data);
}

linked_list linked_list_copy(linked_list list)
{
	null_list_check(list);
	linked_list new_list = linked_list_create();
	node *current = list->head;
	for (int i = 0; i < linked_list_size(list); i++)
	{
		linked_list_add_tail(new_list, current->data);
		current = current->next;
	}
	return new_list;
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
	linked_list_set(list, index1, linked_list_get(list, index2));
	linked_list_set(list, index2, temp);
}

void linked_list_sort(linked_list list)
{
	null_list_check(list);
	empty_list_check(list);
	linked_list_quick_sort_helper(list, 0, linked_list_size(list) - 1);
}

// Helper function for linked_list_sort
void linked_list_quick_sort_helper(linked_list list, int low, int high)
{
	if (low < high)
	{
		int pi = linked_list_partition(list, low, high);
		linked_list_quick_sort_helper(list, low, pi - 1);
		linked_list_quick_sort_helper(list, pi + 1, high);
	}
}

int linked_list_partition(linked_list list, int low, int high)
{
	int pivot = linked_list_get(list, high);
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (linked_list_get(list, j) < pivot)
		{
			i++;
			linked_list_swap(list, i, j);
		}
	}
	linked_list_swap(list, i + 1, high);
	return (i + 1);
}

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

// file deepcode ignore DerefOfMaybeNull: malloc_fail_check is used
// file deepcode ignore CMemoryLeak: the memory is freed in linked_list_destroy
