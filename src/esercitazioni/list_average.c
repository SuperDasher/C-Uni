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
		linked_list_add_tail(list, number);
	}
	linked_list_remove_duplicates(list);
	float average = list_average(list);
	printf("Average: %.2f\n", average);

	return 0;
}

float list_average(linked_list list){
	float sum = 0;
	int count = 0;
	linked_list_iterator it = linked_list_iterator_create(list);
	while (linked_list_iterator_has_next(it))
	{
		int number = linked_list_iterator_next(it);
		sum += number;
		count++;
	}
	linked_list_iterator_destroy(it);
	return sum / count;
}
