#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

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

void print_m_n(int (*mat)[], int rows, int columns, int n)
{
	if (n > rows * columns)
	{
		fprintf(stderr, "n is greater than the number of elements in the matrix\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d\t", *(*mat + i * columns + j));
			if (i * columns + j == n - 1)
			{
				return;
			}
		}
		printf("\n");
	}
}

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

void empty_m(int (*mat)[], int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*mat + i * columns + j) = 0;
		}
	}
}

bool is_empty_m(int (*mat)[], int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (*(*mat + i * columns + j) != 0)
			{
				return false;
			}
		}
	}
	return true;
}

void fill_m(int (*mat)[], int rows, int columns, int value)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*mat + i * columns + j) = value;
		}
	}
}

void randfill_m(int (*mat)[], int rows, int columns, int min, int max)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*mat + i * columns + j) = rand() % (max - min + 1) + min;
		}
	}
}

void succfill_m(int (*mat)[], int rows, int columns)
{
	int value = 1;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*mat + i * columns + j) = value++;
		}
	}
}

typedef int (*__reduce_func_m__)(int, int);
typedef int (*__map_func_m__)(int);
typedef bool (*__filter_func_m__)(int);

int reduce_m(__reduce_func_m__ func, int (*mat)[], int rows, int columns)
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

void map_m(__map_func_m__ func, int (*target)[], int (*mat)[], int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(*target + i * columns + j) = func(*(*mat + i * columns + j));
		}
	}
}

int filter_m(__filter_func_m__ func, int (*target)[], int (*mat)[], int rows, int columns)
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

#endif /* MATRIX_H */
