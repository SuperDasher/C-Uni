#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

/**
 * @brief initialises a dynamic int array with a given size 
 * 
 * @param array 
 * @param size 
 * @param prompt asks for the size of the array 
 */
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

/**
 * @brief asks to fill the int elements of an array 
 * 
 * @param array 
 * @param dim 
 * @param prompt can include "%d" to display the number of elements 
 * - adds a newline after 
 */
void scan_a(int *array, int dim, char *prompt)
{
	char *prompt_newline = (char *)malloc(strlen(prompt) + 2);
	if (prompt_newline == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	strncpy(prompt_newline, prompt, strlen(prompt) + 1);
	strcat(prompt_newline, "\n");
	if (strstr(prompt_newline, "%d"))
		printf(prompt_newline, dim);
	else
		printf("%s", prompt_newline);
	for (int i = 0; i < dim; i++)
	{
		scanf("%d", &array[i]);
	}
	free(prompt_newline);
}

/**
 * @brief prints an int array 
 * 
 * @param array 
 * @param dim 
 */
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

/**
 * @brief assigns zero to every element in an int array 
 * 
 * @param array 
 * @param dim 
 */
void empty_a(int *array, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		array[i] = 0;
	}
}

/**
 * @brief checks if every element in an int array is equal to zero 
 * 
 * @param array 
 * @param dim 
 * @return true if every element in an int array is equal to zero. 
 * @return false if at least one element in an int array is not equal to zero 
 */
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

/**
 * @brief assigns the given value to every element in an int array 
 * 
 * @param array 
 * @param dim 
 * @param value int number to fill the array with 
 */
void fill_a(int *array, int dim, int value)
{
	for (int i = 0; i < dim; i++)
	{
		array[i] = value;
	}
}

/**
 * @brief fill an int array with random values going from min to max 
 * 
 * @param array 
 * @param dim 
 * @param min the minimum randomly generated value that can be assigned to an element of an int array 
 * @param max the maximum randomly generated value that can be assigned to an element of an int array 
 */
void randfill_a(int *array, int dim, int min, int max)
{
	for (int i = 0; i < dim; i++)
	{
		array[i] = rand() % (max - min + 1) + min;
	}
}

/**
 * @brief fills an array with the first natural numbers up to the array size 
 * 
 * @param array 
 * @param dim 
 */
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
