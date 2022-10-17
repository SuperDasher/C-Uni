#include <stdio.h>
#include "../headers/array.h"

#define N 10

void bubble_sort(int *, int);
void swap(int *, int *);

int main()
{
	int array[N];

	scan_a(array, N, "Inserisci i valori dell'array:");

	printf("array prima:\n");
	print_a(array, N);

	bubble_sort(array, N);

	printf("array dopo:\n");
	print_a(array, N);

	return 0;
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

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
