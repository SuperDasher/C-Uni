#ifndef ARRAY_H
#define ARRAY_H

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
	printf("%d]\n", array[dim - 1]);
}

void empty_a(int *array, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		array[i] = 0;
	}
}

bool is_empty_a(int *array, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		if (array[i] != 0)
		{
			return false;
		}
	}
	return true;
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

void succfill_a(int *array, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		array[i] = i + 1;
	}
}

typedef int (*__reduce_func_a__)(int, int);
typedef int (*__map_func_a__)(int);
typedef bool (*__filter_func_a__)(int);

int reduce_a(__reduce_func_a__ func, int *array, int dim)
{
	int result = array[0];
	for (int i = 1; i < dim; i++)
	{
		result = func(result, array[i]);
	}
	return result;
}

void map_a(__map_func_a__ func, int *target, int *array, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		target[i] = func(array[i]);
	}
}

int filter_a(__filter_func_a__ func, int **target, int *array, int dim)
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
	}
	*target = (int *)malloc(target_dim * sizeof(int));
	if (*target == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	for (int i = 0; i < target_dim; i++)
	{
		(*target)[i] = target_full[i];
	}
	free(target_full);
	return target_dim;
}

#endif /* ARRAY_H */
