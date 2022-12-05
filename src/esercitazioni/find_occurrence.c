#include <stdio.h>

int find_occurrence_index(int *, int, int);

int main()
{
	int array[] = {7, 3, 4, 1, 9, 5, 2, 6, 8};
	int size = sizeof(array) / sizeof(array[0]);
	int occurrence = 3;
	int index = find_occurrence_index(array, occurrence, size);
	printf("Occurrence: %d\nIndex: %d\n", occurrence, index);

	return 0;
}

int find_occurrence_index(int *array, int value, int size)
{
	if (size == 0)
		return -1;
	if (array[size - 1] == value)
		return size - 1;
	return find_occurrence_index(array, value, size - 1);
}
