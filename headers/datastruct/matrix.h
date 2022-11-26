#include <stdbool.h>

#ifndef MATRIX_H
#define MATRIX_H

void print_m(int (*mat)[], int rows, int columns);

void print_m_n(int (*mat)[], int rows, int columns, int n);

void scan_m(int (*mat)[], int rows, int columns, char *row_prompt);

void empty_m(int (*mat)[], int rows, int columns);

bool is_empty_m(int (*mat)[], int rows, int columns);

void fill_m(int (*mat)[], int rows, int columns, int value);

void randfill_m(int (*mat)[], int rows, int columns, int min, int max);

void succfill_m(int (*mat)[], int rows, int columns);

int reduce_m(int (*func)(int, int), int (*mat)[], int rows, int columns);

void map_m(int (*func)(int), int (*target)[], int (*mat)[], int rows, int columns);

int filter_m(bool (*func)(int), int (*target)[], int (*mat)[], int rows, int columns);

#endif /* MATRIX_H */
