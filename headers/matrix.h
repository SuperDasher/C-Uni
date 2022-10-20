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

// TODO: convert all these functions to be able to get any type
// TODO: create reduce, map and filter functions
