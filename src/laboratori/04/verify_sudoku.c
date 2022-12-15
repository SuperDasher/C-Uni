#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 9

int sudoku_corretto[N][N] = {
	{5, 8, 6, 4, 2, 1, 3, 7, 9},
	{3, 2, 7, 9, 6, 5, 4, 8, 1},
	{9, 1, 4, 3, 7, 8, 6, 2, 5},

	{1, 6, 3, 5, 8, 4, 7, 9, 2},
	{2, 4, 5, 1, 9, 7, 8, 6, 3},
	{8, 7, 9, 6, 3, 2, 5, 1, 4},

	{7, 5, 8, 2, 1, 3, 9, 4, 6},
	{6, 3, 1, 7, 4, 9, 2, 5, 8},
	{4, 9, 2, 8, 5, 6, 1, 3, 7}};

int sudoku_sbagliato[N][N] = {
	{5, 8, 6, 4, 2, 1, 3, 7, 9},
	{3, 2, 7, 9, 1, 5, 4, 8, 1},
	{9, 1, 4, 3, 7, 8, 6, 2, 5},

	{1, 6, 3, 5, 8, 4, 7, 9, 2},
	{2, 4, 5, 1, 9, 7, 8, 6, 3},
	{8, 7, 4, 6, 3, 2, 5, 1, 4},

	{7, 5, 8, 2, 1, 3, 9, 4, 6},
	{6, 8, 1, 7, 4, 9, 2, 5, 8},
	{4, 9, 2, 8, 5, 2, 1, 3, 7}};

bool are_valid_sudoku_values(int[N][N], int, int);
bool is_valid_sudoku_up_to(int[N][N], int, int);
bool is_valid_sudoku(int[N][N]);
bool is_valid_row(int[N][N], int, int);
bool is_valid_column(int[N][N], int, int);
bool is_valid_subgrid(int[N][N], int, int, int);
void sudoku_file_to_matrix(FILE *, int[N][N]);

int main()
{
	if (is_valid_sudoku(sudoku_corretto) && !is_valid_sudoku(sudoku_sbagliato))
		printf("Esercizio corretto\n");
	else
		printf("Esercizio sbagliato\n");

	FILE *file = fopen("src/files/input/sudoku.txt", "r");
	if (file == NULL)
	{
		perror("Errore apertura file");
		exit(EXIT_FAILURE);
	}
	int file_sudoku[N][N];
	sudoku_file_to_matrix(file, file_sudoku);
	fclose(file);
	if (is_valid_sudoku(file_sudoku))
		printf("sudoku in file valido\n\n");
	else
		printf("sudoku in file non valido\n\n");

	printf("parte 2:\n");
	int input_sudoku[N][N];
	for (int row = 0; row < N; row++)
		for (int column = 0; column < N; column++)
		{
			printf("Inserisci il valore della cella [%d][%d]: ", row, column);
			scanf("%d", &input_sudoku[row][column]);
			if (!is_valid_sudoku_up_to(input_sudoku, row + 1, column + 1))
			{
				printf("Sudoku non valido\n");
				return 0;
			}
		}

	return 0;
}

bool are_valid_sudoku_values(int sudoku[N][N], int up_to_row, int up_to_column)
{
	for (int row = 0; row < up_to_row; row++)
		for (int column = 0; column < up_to_column; column++)
			if (sudoku[row][column] < 1 || sudoku[row][column] > 9)
				return false;
	return true;
}

bool is_valid_sudoku_up_to(int sudoku[N][N], int up_to_row, int up_to_column)
{
	if (!are_valid_sudoku_values(sudoku, up_to_row, up_to_column))
		return false;
	for (int row = 0; row < up_to_row; row++)
		if (!is_valid_row(sudoku, row, up_to_column))
			return false;
	for (int column = 0; column < up_to_column; column++)
		if (!is_valid_column(sudoku, column, up_to_row))
			return false;
	for (int row_shift = 0; row_shift < up_to_row; row_shift += 3)
		for (int column_shift = 0; column_shift < up_to_column; column_shift += 3)
		{
			int up_to_subgrid_row = up_to_row - row_shift > 2 ? 3 : up_to_row - row_shift;
			int up_to_subgrid_column = up_to_column - column_shift > 2 ? 3 : up_to_column - column_shift;
			int up_to_element = (up_to_subgrid_row - 1) * 3 + up_to_subgrid_column;
			if (!is_valid_subgrid(
					sudoku,
					row_shift,
					column_shift,
					up_to_element))
				return false;
		}
	return true;
}

bool is_valid_sudoku(int sudoku[N][N])
{
	if (!are_valid_sudoku_values(sudoku, N, N))
		return false;
	for (int row = 0; row < N; row++)
		if (!is_valid_row(sudoku, row, N))
			return false;
	for (int column = 0; column < N; column++)
		if (!is_valid_column(sudoku, column, N))
			return false;
	for (int row_shift = 0; row_shift < N; row_shift += 3)
		for (int column_shift = 0; column_shift < N; column_shift += 3)
			if (!is_valid_subgrid(sudoku, row_shift, column_shift, N))
				return false;
	return true;
}

bool is_valid_row(int sudoku[N][N], int row, int up_to_column)
{
	for (int check = 0; check < up_to_column; check++)
		for (int compare = 0; compare < up_to_column; compare++)
			if (sudoku[row][check] == sudoku[row][compare] && check != compare)
				return false;
	return true;
}

bool is_valid_column(int sudoku[N][N], int column, int up_to_row)
{
	for (int check = 0; check < up_to_row; check++)
		for (int compare = 0; compare < up_to_row; compare++)
			if (sudoku[check][column] == sudoku[compare][column] && check != compare)
				return false;
	return true;
}

bool is_valid_subgrid(int sudoku[N][N], int row, int column, int up_to_element)
{
	for (int row_check = 0; row_check < 3; row_check++)
		for (int column_check = 0; column_check < 3; column_check++)
		{
			bool skip_to_next = false;
			if (row_check * 3 + column_check == up_to_element)
				return true;
			for (int row_compare = 0; row_compare < 3; row_compare++)
			{
				if (skip_to_next)
					break;
				for (int column_compare = 0; column_compare < 3; column_compare++)
				{
					if (row_compare * 3 + column_compare == up_to_element)
					{
						skip_to_next = true;
						break;
					}
					if (sudoku[row + row_check][column + column_check] == sudoku[row + row_compare][column + column_compare] && (row_check != row_compare || column_check != column_compare))
						return false;
				}
			}
		}
	return true;
}

void sudoku_file_to_matrix(FILE *file, int matrix[N][N])
{
	int number;
	int i = 0;
	int j = 0;
	while (!feof(file))
	{
		number = 0;
		char character = fgetc(file);
		while (character != ',' && character != '\n' && character != EOF)
		{
			number = number * 10 + character - '0';
			character = fgetc(file);
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
