#include <stdbool.h>

#ifndef ARRAY_H
#define ARRAY_H

/**
 * @brief initialises a dynamic int array with a given size
 *
 * @param array
 * @param size
 * @param prompt asks for the size of the array
 */
void init_a(int **array, int *size, char *prompt);

/**
 * @brief asks to fill the int elements of an array
 *
 * @param array
 * @param dim
 * @param prompt can include "%d" to display the number of elements
 * - adds a newline after
 */
void scan_a(int *array, int dim, char *prompt);

/**
 * @brief prints an int array
 *
 * @param array
 * @param dim
 */
void print_a(int *array, int dim);

/**
 * @brief assigns zero to every element in an int array
 *
 * @param array
 * @param dim
 */
void empty_a(int *array, int dim);

/**
 * @brief checks if every element in an int array is equal to zero
 *
 * @param array
 * @param dim
 * @return true if every element in an int array is equal to zero.
 * @return false if at least one element in an int array is not equal to zero
 */
bool is_empty_a(int *array, int dim);

/**
 * @brief assigns the given value to every element in an int array
 *
 * @param array
 * @param dim
 * @param value int number to fill the array with
 */
void fill_a(int *array, int dim, int value);

/**
 * @brief fill an int array with random values going from min to max
 *
 * @param array
 * @param dim
 * @param min the minimum randomly generated value that can be assigned to an element of an int array
 * @param max the maximum randomly generated value that can be assigned to an element of an int array
 */
void randfill_a(int *array, int dim, int min, int max);

/**
 * @brief fills an array with the first natural numbers up to the array size
 *
 * @param array
 * @param dim
 */
void succfill_a(int *array, int dim);

int reduce_a(int (*func)(int, int), int *array, int dim);

void map_a(int (*func)(int), int *target, int *array, int dim);

int filter_a(bool (*func)(int), int **target, int *array, int dim);

#endif /* ARRAY_H */
