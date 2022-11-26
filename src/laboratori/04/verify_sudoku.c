#include <stdio.h>
#include <stdbool.h>

#define N 9

int sudoku_corretto[N][N] = {
	{5, 8, 6,	4, 2, 1,	3, 7, 9},
	{3, 2, 7,	9, 6, 5,	4, 8, 1},
	{9, 1, 4,	3, 7, 8,	6, 2, 5},

	{1, 6, 3,	5, 8, 4,	7, 9, 2},
	{2, 4, 5,	1, 9, 7,	8, 6, 3},
	{8, 7, 9,	6, 3, 2,	5, 1, 4},

	{7, 5, 8,	2, 1, 3,	9, 4, 6},
	{6, 3, 1,	7, 4, 9,	2, 5, 8},
	{4, 9, 2,	8, 5, 6,	1, 3, 7}};

int sudoku_sbagliato[N][N] = {
	{5, 8, 6,	4, 2, 1,	3, 7, 9},
	{3, 2, 7,	9, 1, 5,	4, 8, 1},
	{9, 1, 4,	3, 7, 8,	6, 2, 5},

	{1, 6, 3,	5, 8, 4,	7, 9, 2},
	{2, 4, 5,	1, 9, 7,	8, 6, 3},
	{8, 7, 4,	6, 3, 2,	5, 1, 4},

	{7, 5, 8,	2, 1, 3,	9, 4, 6},
	{6, 8, 1,	7, 4, 9,	2, 5, 8},
	{4, 9, 2,	8, 5, 2,	1, 3, 7}};

bool are_valid_sudoku_values(int [N][N]);
bool is_valid_sudoku(int [N][N]);
bool is_valid_row(int [N][N], int);
bool is_valid_column(int [N][N], int);
bool is_valid_subgrid(int [N][N], int, int);

int main()
{
	if (is_valid_sudoku(sudoku_corretto) && !is_valid_sudoku(sudoku_sbagliato))
		printf("Esercizio corretto");
	else
		printf("Esercizio sbagliato");

	// TODO: finish exercise

	return 0;
}

bool are_valid_sudoku_values(int sudoku[N][N])
{
	for (int row = 0; row < N; row++)
		for (int column = 0; column < N; column++)
			if (sudoku[row][column] < 1 || sudoku[row][column] > 9)
				return false;
	return true;
}

bool is_valid_sudoku(int sudoku[N][N])
{
	if (!are_valid_sudoku_values(sudoku))
		return false;
	for (int row = 0; row < N; row++)
		if(!is_valid_row(sudoku, row))
			return false;
	for (int column = 0; column < N; column++)
		if (!is_valid_column(sudoku, column))
			return false;
	for (int row_shift = 0; row_shift < N; row_shift += 3)
		for (int column_shift = 0; column_shift < N; column_shift += 3)
			if (!is_valid_subgrid(sudoku, row_shift, column_shift))
				return false;
	return true;
}

bool is_valid_row(int sudoku[N][N], int row)
{
	for (int check = 0; check < N; check++)
		for (int compare = 0; compare < N; compare++)
			if (sudoku[row][check] == sudoku[row][compare] && check != compare)
				return false;
	return true;
}

bool is_valid_column(int sudoku[N][N], int column)
{
	for (int check = 0; check < N; check++)
		for (int compare = 0; compare < N; compare++)
			if (sudoku[check][column] == sudoku[compare][column] && check != compare)
				return false;
	return true;
}

bool is_valid_subgrid(int sudoku[N][N], int row, int column)
{
	for (int row_check = 0; row_check < 3; row_check++)
		for (int column_check = 0; column_check < 3; column_check++)
			for (int row_compare = 0; row_compare < 3; row_compare++)
				for (int column_compare = 0; column_compare < 3; column_compare++)
					if (sudoku[row + row_check][column + column_check] == sudoku[row + row_compare][column + column_compare] && (row_check != row_compare || column_check != column_compare))
						return false;
	return true;
}
