#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_a(int **array, int *size, char *prompt)
{
	printf("%s", prompt);
	scanf("%d", size);
	*array = (int *)malloc(*size * sizeof(int));
	if (*array == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
}

void scan_a(int *array, int dim, char *prompt)
{
	printf("%s\n", prompt);
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

typedef (*reduce_func)(int, int);
typedef (*map_func)(int);
typedef (*filter_func)(int);

int reduce(reduce_func func, int *array, int dim)
{
	int result = array[0];
	for (int i = 1; i < dim; i++)
	{
		result = func(result, array[i]);
	}
	return result;
}

int *map(map_func func, int *array, int dim)
{
	int *result = (int *)malloc(dim * sizeof(int));
	if (result == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	for (int i = 0; i < dim; i++)
	{
		result[i] = func(array[i]);
	}
	return result;
}

struct filter_result
{
	int *array;
	int dim;
};

struct filter_result filter(filter_func func, int *array, int dim)
{
	struct filter_result result;
	result.array = (int *)malloc(dim * sizeof(int));
	if (result.array == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	result.dim = 0;
	for (int i = 0; i < dim; i++)
	{
		if (func(array[i]))
		{
			result.array[result.dim] = array[i];
			result.dim++;
		}
	}
	return result;
}

// TODO: convert all these functions to be able to get any type of array
