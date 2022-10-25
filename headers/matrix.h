#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

// TODO: make function not pass rows and columns as parameters
// TODO: convert all these functions to be able to get any type of static matrix

void print_m(int (*mat)[], int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d\t", *(*mat + i * columns + j));
		}
		printf("\n");
	}
}

// TODO: create function to print first n elements of matrix

void scan_m(int (*mat)[], int rows, int columns, char *row_prompt)
{
	char *row_prompt_end = (char *)malloc((strlen(row_prompt) + 2) * sizeof(char));
	if (row_prompt_end == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	strncpy(row_prompt_end, row_prompt, strlen(row_prompt) + 1);
	strcat(row_prompt_end, "\n");
	if (strstr(row_prompt, "%d") != NULL)
	{
		for (int i = 0; i < rows; i++)
		{
			printf(row_prompt_end, i + 1);
			for (int j = 0; j < columns; j++)
			{
				scanf("%d", *mat + i * columns + j);
			}
		}
		free(row_prompt_end);
		return;
	}
	for (int i = 0; i < rows; i++)
	{
		printf("%s", row_prompt_end);
		for (int j = 0; j < columns; j++)
		{
			scanf("%d", *mat + i * columns + j);
		}
	}
	free(row_prompt_end);
}

void empty_dm(int (*mat)[], int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*mat + i * columns + j) = 0;
		}
	}
}

// TODO: bool is_empty()

void fill_dm(int (*mat)[], int rows, int columns, int value)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*mat + i * columns + j) = value;
		}
	}
}

void randfill_dm(int (*mat)[], int rows, int columns, int min, int max)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*mat + i * columns + j) = rand() % (max - min + 1) + min;
		}
	}
}

typedef int (*reduce_func_m)(int, int);
typedef int (*map_func_m)(int);
typedef bool (*filter_func_m)(int);

int reduce_m(reduce_func_m func, int (*mat)[], int rows, int columns)
{
	int result = *(*mat + 0 * columns + 0);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result = func(result, *(*mat + i * columns + j));
		}
	}
	return result;
}

void map_m(map_func_m func, int (*target)[], int (*mat)[], int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*target + i * columns + j) = func(*(*mat + i * columns + j));
		}
	}
}

int filter_m(filter_func_m func, int (*target)[], int (*mat)[], int rows, int columns)
{
	int target_dim = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (func(*(*mat + i * columns + j)))
			{
				*(*target + target_dim) = *(*mat + i * columns + j);
				target_dim++;
			}
		}
	}
	for (int i = target_dim; i < rows * columns; i++)
	{
		*(*target + i) = 0;
	}
	return target_dim;
}
