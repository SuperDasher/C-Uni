#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

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

typedef int (*reduce_func_a)(int, int);
typedef int (*map_func_a)(int);
typedef bool (*filter_func_a)(int);

int reduce_a(reduce_func_a func, int *array, int dim)
{
	int result = array[0];
	for (int i = 1; i < dim; i++)
	{
		result = func(result, array[i]);
	}
	return result;
}

void map_a(map_func_a func, int *target, int *array, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		target[i] = func(array[i]);
	}
}

int filter_a(filter_func_a func, int **target, int *array, int dim)
{
	int *target_full = (int *)malloc(dim * sizeof(int));
	if (target_full == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	int target_dim = 0;
	for (int i = 0; i < dim; i++)
	{
		if (func(array[i]))
		{
			target_full[target_dim] = array[i];
			target_dim++;
		}
		printf("cur dimension: %d\n", target_dim);
	}
	*target = (int *)malloc(target_dim * sizeof(int));
	if (*target == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	printf("dimension: %d\n", target_dim);
	for (int i = 0; i < target_dim; i++)
	{
		printf("start %d\n", i);
		(*target)[i] = target_full[i];
	}
	free(target_full);
	return target_dim;
}

// TODO: convert all these functions to be able to get any type of array
