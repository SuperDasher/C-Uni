#ifndef INTSORT_H
#define INTSORT_H

#include <intsort/bubble.h>
#include <intsort/quick.h>

bool is_sorted(int *array, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		if (array[i] > array[i + 1])
		{
			return false;
		}
	}
	return true;
}

#endif /* INTSORT_H */
