#include <stdio.h>
#include <stdlib.h>
#include <custom/datastruct.h>

int xy_concatenate_count(int *, int, int, int);

int main()
{
	int length = 0;
	int x, y;
	printf("Inserisci la lunghezza dell'array: ");
	scanf("%d", &length);
	if (length < 2)
	{
		fprintf(stderr, "L'array deve avere almeno due elementi\n");
		exit(EXIT_FAILURE);
	}
	int *array = malloc(length * sizeof(int));
	if (array == NULL)
	{
		perror("malloc() failed");
		exit(errno);
	}
	scan_a(array, length, "Inserisci l'array: ");
	printf("Inserisci x e y: ");
	scanf("%d %d", &x, &y);
	if (xy_concatenate_count(array, length, x, y) == -1)
		printf("L'array non contiene il valore %d\n", x);
	printf("Il numero di volte che x e y si sono concatenati e' %d\n", xy_concatenate_count(array, length, x, y));
	free(array);
	return 0;
}

int xy_concatenate_count(int *array, int length, int x, int y)
{
	if (length < 2)
		return -1;
	int count = xy_concatenate_count(array, length - 1, x, y);
	if (array[length - 2] == x)
	{
		if (count == -1)
			count = 0;
		if (array[length - 1] == y)
			count++;
	}
	if (array[length - 1] == x && count == -1)
		count = 0;
	return count;
}
