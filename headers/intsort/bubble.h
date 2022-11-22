#include <swap.h>

void bubble_sort(int *array, int length)
{
	for (int len = length - 1; len > 0; len--)
	{
		for (int i = 0; i < len; i++)
		{
			if (array[i] > array[i + 1])
			{
				swap(&array[i], &array[i + 1]);
			}
		}
	}
}
