#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <custom/datastruct.h>

int main()
{
	srand(time(NULL));
	int **a, **b, **result;
	unsigned int n, m;
	printf("quali dimensioni vuoi per le matrici?\n");
	printf("righe: ");
	scanf("%u", &n);
	printf("colonne: ");
	scanf("%u", &m);

	if (!malloc_m(&a, n, m) ||
		!malloc_m(&b, n, m) ||
		!malloc_m(&result, n, m))
	{
		perror("malloc_m() failed");
		exit(errno);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			a[i][j] = rand() % 41 - 20;
			b[i][j] = rand() % 41 - 20;
			result[i][j] = a[i][j] + b[i][j];
		}
	}

	printf("prima matrice:\n");
	print_dm(a, n, m);
	printf("seconda matrice:\n");
	print_dm(b, n, m);
	printf("somma:\n");
	print_dm(result, n, m);

	free_m(a, n);
	free_m(b, n);
	free_m(result, n);

	return 0;
}
