#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef (*reduce_func)(int, int);
typedef (*map_func)(int);
typedef (*filter_func)(int);

int reduce(int (*mat)[], int rows, int columns, reduce_func func)
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

int *map(int (*mat)[], int rows, int columns, map_func func)
{
	int *result = (int *)malloc(rows * columns * sizeof(int));
	if (result == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*(result + i * columns + j) = func(*(*mat + i * columns + j));
		}
	}
	return result;
}

struct filter_result
{
	int *result;
	int size;
};

struct filter_result filter(int (*mat)[], int rows, int columns, filter_func func)
{
	struct filter_result result;
	result.result = (int *)malloc(rows * columns * sizeof(int));
	if (result.result == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	result.size = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (func(*(*mat + i * columns + j)))
			{
				*(result.result + result.size) = *(*mat + i * columns + j);
				result.size++;
			}
		}
	}
	return result;
}

// TODO: convert all these functions to be able to get any type of static matrix
