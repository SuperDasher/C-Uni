#include <intsort/quick.h>

#include <custom/swap.h>

int partition(int *array, int left, int right)
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

void quick_sort_helper(int *array, int left, int right)
{
	if (left < right)
	{
		int pivot = partition(array, left, right);
		quick_sort_helper(array, left, pivot - 1);
		quick_sort_helper(array, pivot + 1, right);
	}
}

void quick_sort(int *array, int length)
{
	quick_sort_helper(array, 0, length - 1);
}
