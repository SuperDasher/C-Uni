#include <stdio.h>
#include <stdlib.h>

int max_value(int *, int);
int min_value(int *, int);

int main()
{
	int array[] = {7, 3, 4, 1, 9, 5, 2, 6, 8};
	int size = sizeof(array) / sizeof(array[0]);
	int max = max_value(array, size);
	int min = min_value(array, size);
	printf("Max: %d\nMin: %d\n", max, min);

	return 0;
}

int max_value(int *array, int size)
{
	if (size == 0)
		return INT_MAX;
	if (size == 1)
		return *array;
	int max = max_value(array, size - 1);
	if (max < array[size - 1])
		return array[size - 1];
	else
		return max;
}

int min_value(int *array, int size)
{
	if (size == 0)
		return INT_MIN;
	if (size == 1)
		return *array;
	int min = min_value(array, size - 1);
	if (min > array[size - 1])
		return array[size - 1];
	else
		return min;
}
