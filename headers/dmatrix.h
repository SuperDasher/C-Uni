#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void scan_dm(int **mat, int rows, int columns, char row_prompt[])
{
	char *row_prompt_end = (char *)malloc((strlen(row_prompt) + 2) * sizeof(char));
	if (row_prompt_end == NULL)
	{
		// FIXME: add error message for negative numbers
		printf("out of memory\n");
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

void empty_m(int **mat, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] = 0;
		}
	}
}

void fill_m(int **mat, int rows, int columns, int value)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] = value;
		}
	}
}

void randfill_m(int **mat, int rows, int columns, int min, int max)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mat[i][j] = rand() % (max - min + 1) + min;
		}
	}
}
