#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <custom/intsort.h>
#include <custom/datastruct.h>

#define ARRAY_LEN 10

int main()
{
	int v[ARRAY_LEN];
	int low = 0, high = ARRAY_LEN;
	int number;

	scan_a(v, ARRAY_LEN, "popola l'array con 10 elementi");
	printf("che valore vuoi trovare nell'array?\n");
	scanf("%d", &number);
	quick_sort(v, ARRAY_LEN);

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
