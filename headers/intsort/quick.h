#include <swap.h>

static int partition(int *array, int left, int right)
{
	int pivot = array[right];
	int i = left;
	for (int j = left; j < right; j++)
	{
		if (array[j] < pivot)
		{
			swap(&array[i], &array[j]);
			i++;
		}
	}
	swap(&array[i], &array[right]);
	return i;
}

void quick_sort(int *array, int left, int right)
{
	if (left < right)
	{
		int pivot = partition(array, left, right);
		quick_sort(array, left, pivot - 1);
		quick_sort(array, pivot + 1, right);
	}
}
