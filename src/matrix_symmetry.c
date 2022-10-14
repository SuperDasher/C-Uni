#include <stdio.h>
#include <stdbool.h>

#define DIM 5

int main()
{
    int m[DIM][DIM];
    for (int i = 0; i < DIM; i++)
    {
        printf("inserisci i valori della riga %d:\n", i + 1);
        for (int j = 0; j < DIM; j++)
        {
            scanf("%d", &m[i][j]);
        }
    }

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
