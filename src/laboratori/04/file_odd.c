#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <custom/datastruct.h>

#define MATRIX_SIZE 5

bool is_odd(int);
bool file_format_valid(FILE *);
void csv_to_matrix(FILE *, int[MATRIX_SIZE][MATRIX_SIZE]);
void write_matrix_to_file(FILE *, int[MATRIX_SIZE][MATRIX_SIZE]);

int main()
{
	int matrix[MATRIX_SIZE][MATRIX_SIZE];
	int odd_matrix[MATRIX_SIZE][MATRIX_SIZE];
	FILE *file = fopen("src/files/input/matrice.txt", "r");
	if (file == NULL)
	{
		perror("Error opening file");
		exit(errno);
	}
	if (!file_format_valid(file))
	{
		fprintf(stderr, "File not valid\n");
		exit(EXIT_FAILURE);
	}
	rewind(file);
	csv_to_matrix(file, matrix);
	fclose(file);

	filter_m(is_odd, odd_matrix, matrix, MATRIX_SIZE, MATRIX_SIZE);
	file = fopen("src/files/output/matrice_dispari.txt", "w");
	if (file == NULL)
	{
		perror("Error opening file");
		exit(errno);
	}
	write_matrix_to_file(file, odd_matrix);
	fclose(file);

	return 0;
}

bool is_odd(int n)
{
	return n % 2 == 1;
}

bool file_format_valid(FILE *file)
{
	int line_numbers = 0;
	int columns = 0;
	char character = 0;
	while (!feof(file))
	{
		character = fgetc(file);
		if (character == ',')
			line_numbers++;
		else if (character == '\n')
		{
			if (line_numbers != MATRIX_SIZE - 1)
				return false;
			columns++;
			line_numbers = 0;
		}
	}
	if (line_numbers != MATRIX_SIZE - 1 || columns != MATRIX_SIZE - 1)
		return false;
	return true;
}

void csv_to_matrix(FILE *file, int matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int number;
	bool negative = false;
	int i = 0;
	int j = 0;
	while (!feof(file))
	{
		number = 0;
		char character = fgetc(file);
		if (character == '-')
		{
			negative = true;
			character = fgetc(file);
		}
		while (character != ',' && character != '\n' && character != EOF)
		{
			number = number * 10 + character - '0';
			character = fgetc(file);
		}
		if (negative)
		{
			number = -number;
			negative = false;
		}
		matrix[i][j] = number;
		if (character == ',')
			j++;
		else
		{
			i++;
			j = 0;
		}
	}
}

void write_matrix_to_file(FILE *file, int matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			fprintf(file, "%d", matrix[i][j]);
			if (j != MATRIX_SIZE - 1)
				fprintf(file, ",");
		}
		fprintf(file, "\n");
	}
}
