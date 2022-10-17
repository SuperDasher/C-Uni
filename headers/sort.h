void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

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

void quick_sort(int *array, int left, int right)
{
	if (left < right)
	{
		int pivot = partition(array, left, right);
		quick_sort(array, left, pivot - 1);
		quick_sort(array, pivot + 1, right);
	}
}

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
