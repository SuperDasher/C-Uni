#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *array, int left, int right);
int partition(int *array, int left, int right);
void swap(int *a, int *b);

int main(int argc, char *argv[])
{
	argv++;
	argc--;

	if (argc < 2)
	{
		printf("usage: %s <number> <number> <number> ...\n", argv[-1]);
		return 1;
	}

	int *numbers = malloc(argc * sizeof(int));
	printf("array di parametri prima del sort:\n{");
	for (int i = 0; i < argc - 1; i++)
	{
		numbers[i] = atoi(argv[i]);
		printf("%d, ", numbers[i]);
	}
	numbers[argc - 1] = atoi(argv[argc - 1]);
	printf("%d}\n", numbers[argc - 1]);

	quick_sort(numbers, 0, argc - 1);

	printf("\narray di parametri dopo il sort:\n{");
	for (int i = 0; i < argc - 1; i++)
	{
		printf("%d, ", numbers[i]);
	}
	printf("%d}\n", numbers[argc - 1]);
	free(numbers);

	return 0;
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

int partition(int *array, int left, int right)
{
	int pivot = array[right];
	int i = left - 1;
	for (int j = left; j < right; j++)
	{
		if (array[j] < pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[right]);
	return i + 1;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}