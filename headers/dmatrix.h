#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

bool malloc_m(int ***mat, int rows, int columns)
{
	*mat = (int **)malloc(rows * sizeof(int *));
	if (*mat == NULL)
		return false;
	for (int i = 0; i < rows; i++)
	{
		*(*mat + i) = (int *)malloc(columns * sizeof(int));
		if (*(*mat + i) == NULL)
			return false;
	}
	return true;
}

void init_m(int ***mat, int *rows, int *columns, char *prompt, char *row_prompt, char *column_prompt)
{
	printf("%s\n", prompt);
	printf("%s", row_prompt);
	scanf("%d", rows);
	printf("%s", column_prompt);
	scanf("%d", columns);
	if (!malloc_m(mat, *rows, *columns))
	{
		fprintf(stderr, "malloc_m() failed: %s\n", strerror(errno));
		exit(errno);
	}
}

void free_m(int ***mat, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(*(*mat + i));
	}
	free(*mat);
}

void print_dm(int **mat, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
}

void print_dm_n(int **mat, int rows, int columns, int n)
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
			printf("%d\t", mat[i][j]);
			if (--n == 0)
				return;
		}
		printf("\n");
	}
}

void scan_dm(int **mat, int rows, int columns, char *row_prompt)
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
				scanf("%d", &mat[i][j]);
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
			scanf("%d", &mat[i][j]);
		}
	}
	free(row_prompt_end);
}

void empty_dm(int **mat, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] = 0;
		}
	}
}

bool is_empty_dm(int **mat, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (mat[i][j] != 0)
				return false;
		}
	}
	return true;
}

void fill_dm(int **mat, int rows, int columns, int value)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] = value;
		}
	}
}

void randfill_dm(int **mat, int rows, int columns, int min, int max)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] = rand() % (max - min + 1) + min;
		}
	}
}

void succfill_dm(int **mat, int rows, int columns)
{
	int value = 1;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] = value++;
		}
	}
}

typedef int (*reduce_func_dm)(int, int);
typedef int (*map_func_dm)(int);
typedef bool (*filter_func_dm)(int);

int reduce_dm(reduce_func_dm func, int **mat, int rows, int columns)
{
	int result = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result = func(result, mat[i][j]);
		}
	}
	return result;
}

void map_dm(map_func_dm func, int ***target, int **mat, int rows, int columns)
{
	if (!malloc_m(target, rows, columns))
	{
		fprintf(stderr, "malloc_m() failed: %s\n", strerror(errno));
		exit(errno);
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			*target[i][j] = func(mat[i][j]);
		}
	}
}

int filter_dm(filter_func_dm func, int ***target, int **mat, int rows, int columns)
{
	if (!malloc_m(target, rows, columns))
	{
		fprintf(stderr, "malloc_m() failed: %s\n", strerror(errno));
		exit(errno);
	}
	int target_dim = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (func(mat[i][j]))
			{
				(*target)[target_dim / rows][target_dim % rows] = mat[i][j];
				target_dim++;
			}
		}
	}
	for (int i = target_dim; i < rows * columns; i++)
	{
		(*target)[i / rows][i % rows] = 0;
	}
	return target_dim;
}
