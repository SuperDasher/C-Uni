#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <custom/datastruct.h>

#define SUBMATRIX_SIZE 3

int main()
{
	int **matrix;
	int rows, columns;
	init_m(&matrix, &rows, &columns, "Inserisci le dimensioni della matrice", "Righe: ", "Colonne: ");
	if (rows < SUBMATRIX_SIZE || columns < SUBMATRIX_SIZE)
	{
		fprintf(stderr, "La matrice deve avere almeno %d righe e %d colonne", SUBMATRIX_SIZE, SUBMATRIX_SIZE);
		exit(EXIT_FAILURE);
	}
	scan_dm(matrix, rows, columns, "Riga %d:");

	for (int i = 0; i < rows - SUBMATRIX_SIZE; i++)
	{
		for (int j = 0; j < columns - SUBMATRIX_SIZE; j++)
		{
			int **submatrix;
			if (!malloc_m(&submatrix, SUBMATRIX_SIZE, SUBMATRIX_SIZE))
			{
				fprintf(stderr, "malloc_m() failed: %s\n", strerror(errno));
				exit(errno);
			}
			for (int k = 0; k < SUBMATRIX_SIZE; k++)
			{
				for (int l = 0; l < SUBMATRIX_SIZE; l++)
				{
					submatrix[k][l] = matrix[i + k][j + l];
				}
			}
			if (is_empty_dm(submatrix, SUBMATRIX_SIZE, SUBMATRIX_SIZE))
			{
				printf("Sotto-matrice vuota trovata in posizione (%d, %d)\n", i + 1, j + 1);
				return 0;
			}
		}
	}
	printf("Nessuna sotto-matrice vuota trovata\n");

	return 0;
}
