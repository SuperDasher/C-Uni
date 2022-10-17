#include <stdio.h>
#include <stdbool.h>
#include "../headers/sort.h"

#define ARRAY_LEN 10

int main()
{
	int v[ARRAY_LEN];
	int low = 0, high = ARRAY_LEN;
	int number;

	printf("popola l'array con 10 elementi\n");
	for (int i = 0; i < ARRAY_LEN; i++)
	{
		scanf("%d", &v[i]);
	}
	printf("che valore vuoi trovare nell'array?\n");
	scanf("%d", &number);
	quick_sort(v, 0, ARRAY_LEN - 1);

	while (low <= high)
	{
		int index = (low + high) / 2;
		if (v[index] == number)
		{
			printf("il valore e' presente nell'array\n");
			return 0;
		}
		if (v[index] > number)
		{
			high = index - 1;
			continue;
		}
		low = index + 1;
	}
	printf("il valore non e' presente nell'array\n");

	return 0;
}
