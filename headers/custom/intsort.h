#include <stdbool.h>

#ifndef INTSORT_H
#define INTSORT_H

#include <intsort/bubble.h>
#include <intsort/quick.h>
#include <custom/swap.h>

bool is_sorted(int *array, int length);

void shuffle(int *array, int length);

#endif /* INTSORT_H */
