#include <stdio.h>
#include <stdlib.h>
#include <list/linked.h>

void list_sum(linked_list_iterator);

int main()
{
	linked_list list = linked_list_create();
	for (int i = 1; i <= 10; i++)
		linked_list_insert(list, i);
	linked_list_iterator it = linked_list_iterator_begin(list);
	list_sum(it);
	linked_list_iterator_destroy(it);
	linked_list_print(list);
	linked_list_destroy(&list);

	return 0;
}

void list_sum(linked_list_iterator iterator)
{
	int previous_number = linked_list_iterator_data(iterator);
	linked_list_iterator_next(iterator);
	int current_number = linked_list_iterator_data(iterator);
	linked_list_iterator current_iterator = linked_list_iterator_copy(iterator);
	if (linked_list_iterator_has_next(iterator))
	{
		list_sum(iterator);
	}
	linked_list_iterator_set(current_iterator, current_number + previous_number);
}
