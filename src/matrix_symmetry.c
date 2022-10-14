#include <stdio.h>
#include <stdbool.h>
#include "../headers/matrix.h"

#define DIM 5

int main()
{
	int m[DIM][DIM];
	scan_m(m, DIM, DIM, "inserisci i valori della riga %d:");

	for (int i = 0; i < DIM - 1; i++)
	{
		for (int j = i + 1; j < DIM; j++)
		{
			if (m[i][j] != m[j][i])
			{
				printf("la matrice non e' simmetrica\n");
				return 0;
			}
		}
	}
	printf("la matrice e' simmetrica\n");

	return 0;
}
