#include <stdio.h>
#include <stdlib.h>
#include <list/linked.h>

float list_average(linked_list);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <numbers...>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	linked_list list = linked_list_create();
	for (int i = 1; i < argc; i++)
	{
		int number = atoi(argv[i]);
		linked_list_insert(list, number);
	}
	linked_list_remove_duplicates(list);
	float average = list_average(list);
	printf("Average: %.2f\n", average);
	linked_list_destroy(&list);

	return 0;
}

float list_average(linked_list list)
{
	if (linked_list_is_empty(list))
		return 0;
	float sum = 0;
	int count = 0;
	linked_list_iterator it = linked_list_iterator_begin(list);
	while (linked_list_iterator_has_next(it))
	{
		int number = linked_list_iterator_data(it);
		linked_list_iterator_next(it);
		sum += number;
		count++;
	}
	linked_list_iterator_destroy(it);
	// deepcode ignore DivisionByZero: linked_list_is_empty() checks if the list is empty
	return sum / count;
}
