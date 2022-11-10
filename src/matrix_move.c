/* TODO: reminder: finish all the assignments on WeBeep
	remaining ones: 6 (this one) - 7
*/
#include <stdio.h>
#include <matrix.h>

#define N 3
#define K 5

enum movement
{
	BACK = -1,
	NONE,
	FORWARD,
};
struct move
{
	enum movement row;
	enum movement col;
};

int main()
{
	int matrix[N][N] = { 0 };
	succfill_m(matrix, N, N);
	struct move a[K];

	print_m(matrix, N, N);
	printf("\n");
	printf("parti dalla cella con indici (0, 0)\nalla fine verra' calcola la somma di tutti i numeri incontrati\nle mosse da fare sono %d:\ninserisci -1 per un movimento all'indietro, 0 per non muoversi, 1 per andare avanti, rispettivamente per riga e colonna\n\n", K);

	int row = 0, col = 0;
	int sum = matrix[row][col];

	for (int i = 0; i < K; i++)
	{
		printf("mossa %d: ", i + 1);
		scanf("%d%d", &a[i].row, &a[i].col);
		while (a[i].row < BACK || a[i].row > FORWARD || a[i].col < BACK || a[i].col > FORWARD)
		{
			printf("formato non valido, riprova:\n");
			printf("mossa %d: ", i + 1);
			scanf("%d%d", &a[i].row, &a[i].col);
		}
		row += a[i].row;
		col += a[i].col;
		if (row < 0 || row >= N || col < 0 || col >= N)
		{
			fprintf(stderr, "errore: movimento non valido\n");
			exit(EXIT_FAILURE);
		}
		sum += matrix[row][col];
	}

	printf("la somma degli indici visitati e' %d\n", sum);
	
	return 0;
}