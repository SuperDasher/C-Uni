#include <custom/intsort.h>

#include <stdlib.h>

bool is_sorted(int *array, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		if (array[i] > array[i + 1])
		{
			return false;
		}
	}
	return true;
}

void shuffle(int *array, int length)
{
	for (int i = 0; i < length; i++)
	{
		int j = rand() % length;
		swap(&array[i], &array[j]);
	}
}
