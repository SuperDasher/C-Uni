#include <stdio.h>
#include <stdlib.h>
#include <custom/datastruct.h>
#include <custom/intsort.h>

void concatenate_ordered_recursive(int *, int, int *, int, int *);

int main()
{
	int *array1, *array2, *result;
	int length1, length2, length_result;
	init_a(&array1, &length1, "quanti elementi nell'array1? ");
	init_a(&array2, &length2, "quanti elementi nell'array2? ");
	scan_a(array1, length1, "inserisci elementi array1 (%d elementi): ");
	scan_a(array2, length2, "inserisci elementi array2 (%d elementi): ");
	quick_sort(array1, length1);
	quick_sort(array2, length2);
	length_result = length1 + length2;
	result = malloc(length_result * sizeof(int));
	if (result == NULL)
	{
		perror("malloc failed");
		exit(errno);
	}

	concatenate_ordered_recursive(array1, length1, array2, length2, result);
	printf("1: ");
	print_a(array1, length1);
	printf("2: ");
	print_a(array2, length2);
	printf("result: ");
	print_a(result, length_result);

	free(array1);
	free(array2);
	free(result);

	return 0;
}

void concatenate_ordered_recursive(int *array1, int length1, int *array2, int length2, int *result)
{
	if (!is_sorted(array1, length1) || !is_sorted(array2, length2))
		return;
	if (length1 == 0 && length2 == 0)
		return;
	if (length1 == 0)
	{
		*result = *array2;
		concatenate_ordered_recursive(array1, length1, array2 + 1, length2 - 1, result + 1);
	}
	else if (length2 == 0)
	{
		*result = *array1;
		concatenate_ordered_recursive(array1 + 1, length1 - 1, array2, length2, result + 1);
	}
	else if (*array1 < *array2)
	{
		*result = *array1;
		concatenate_ordered_recursive(array1 + 1, length1 - 1, array2, length2, result + 1);
	}
	else
	{
		*result = *array2;
		concatenate_ordered_recursive(array1, length1, array2 + 1, length2 - 1, result + 1);
	}
}
