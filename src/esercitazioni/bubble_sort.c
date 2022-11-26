#include <stdio.h>
#include <custom/datastruct.h>
#include <custom/intsort.h>

#define N 10

int main()
{
	int array[N];

	scan_a(array, N, "Inserisci i valori dell'array:");

	printf("array prima:\n");
	print_a(array, N);

	bubble_sort(array, N);

	printf("array dopo:\n");
	print_a(array, N);

	return 0;
}
