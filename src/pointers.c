#include <custom/datastruct.h>

#define N 50

int main()
{
	int array[N];
	randfill_a(array, N, 1, 30);
	int *pointer = array;
	printf("indirizzo array:\t%p\n", (void *)array);
	printf("indirizzo array[0]:\t%p\n", (void *)&array[0]);
	printf("indirizzo pointer:\t%p\n", (void *)pointer);

	printf("primo elemento array: %d\n", array[0]);
	printf("valore dereferenziato pointer: %d\n", *pointer);

	printf("stampo array tramite array:\n");
	for (int i = 0; i < N; i++)
		printf("%d ", array[i]);

	printf("\nstampo array tramite pointer:\n");
	for (int i = 0; i < N; i++)
		printf("%d ", *(pointer + i));
	printf("\n");

	return 0;
}
