#include <stdbool.h>

#ifndef DMATRIX_H
#define DMATRIX_H

bool malloc_m(int ***mat, int rows, int columns);

void init_m(int ***mat, int *rows, int *columns, char *prompt, char *row_prompt, char *column_prompt);

void free_m(int **mat, int rows);

void print_dm(int **mat, int rows, int columns);

void print_dm_n(int **mat, int rows, int columns, int n);

void scan_dm(int **mat, int rows, int columns, char *row_prompt);

void empty_dm(int **mat, int rows, int columns);

bool is_empty_dm(int **mat, int rows, int columns);

void fill_dm(int **mat, int rows, int columns, int value);

void randfill_dm(int **mat, int rows, int columns, int min, int max);

void succfill_dm(int **mat, int rows, int columns);

int reduce_dm(int (*func)(int, int), int **mat, int rows, int columns);

void map_dm(int (*func)(int), int ***target, int **mat, int rows, int columns);

int filter_dm(bool (*func)(int), int ***target, int **mat, int rows, int columns);

#endif /* MATRIX_H */
