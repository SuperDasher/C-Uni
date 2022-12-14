#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <custom/datastruct.h>

int main()
{
	int **a, **b, **result;
	int rows_a, cols_a, rows_b, cols_b;
	init_m(&a, &rows_a, &cols_a, "Inserisci i valori della prima matrice:", "Righe: ", "Colonne: ");

	printf("La seconda matrice sara' di %d righe:\n", cols_a);
	rows_b = cols_a;

	printf("Inserisci il numero di colonne della seconda matrice:\n");
	scanf("%d", &cols_b);
	if (!malloc_m(&b, rows_b, cols_b))
	{
		perror("malloc() failed");
		exit(errno);
	}

	if (!malloc_m(&result, rows_a, cols_b))
	{
		perror("malloc() failed");
		exit(errno);
	}

	printf("Inserisci i valori della prima matrice (%dx%d):\n", rows_a, cols_a);
	scan_dm(a, rows_a, cols_a, "riga %d");

	printf("Inserisci i valori della seconda matrice (%dx%d):\n", rows_b, cols_b);
	scan_dm(b, rows_b, cols_b, "riga %d");

	printf("Il prodotto fra le due matrici e':\n");
	for (int i = 0; i < rows_a; i++)
	{
		for (int j = 0; j < cols_b; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < cols_a; k++)
			{
				result[i][j] += a[i][k] * b[k][j];
			}
			printf("%d\t", result[i][j]);
		}
		printf("\n");
	}
	free_m(a, rows_a);
	free_m(b, rows_b);
	free_m(result, rows_a);

	return 0;
}
