#include <stdio.h>
#include <stdlib.h>

void scan_a(int *array, int dim, char *prompt)
{
	printf("%s", prompt);
	for (int i = 0; i < dim; i++)
	{
		scanf("%d", &array[i]);
	}
}

void print_a(int *array, int dim)
{
	if (dim < 2)
	{
		printf("[%d]", array[0]);
		return;
	}
	printf("[%d, ", array[0]);
	for (int i = 1; i < dim - 1; i++)
	{
		printf("%d, ", array[i]);
	}
	printf("%d]", array[dim - 1]);
}

void empty_a(int *array, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		array[i] = 0;
	}
}

void fill_a(int *array, int dim, int value)
{
	for (int i = 0; i < dim; i++)
	{
		array[i] = value;
	}
}

void randfill_a(int *array, int dim, int min, int max)
{
	for (int i = 0; i < dim; i++)
	{
		array[i] = rand() % (max - min + 1) + min;
	}
}
