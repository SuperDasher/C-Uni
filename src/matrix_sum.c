#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

bool m_malloc(int **, int, int);
void print_m(int **, int, int);

int main()
{
    srandom(time(NULL));
    int **a, **b, **result;
    unsigned int n, m;
    printf("quali dimensioni vuoi per le matrici?\n");
    scanf("%u%u", &n, &m);

    if (!m_malloc(a, n, m) || !m_malloc(b, n, m) || !m_malloc(result, n, m))
    {
        printf("out of memory\n");
        exit(errno);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = random() % 41 - 20;
            b[i][j] = random() % 41 - 20;
            result[i][j] = a[i][j];
        }
    }

    printf("prima matrice:\n");
    print_m(a, n, m);
    printf("prima matrice:\n");
    print_m(b, n, m);
    printf("somma:\n");
    print_m(result, n, m);

    return 0;
}

bool m_malloc(int **mat, int rows, int columns)
{
    mat = (int **)malloc(rows * sizeof(int *));
    if (mat == NULL)
        return false;
    for (int i = 0; i < rows; i++)
    {
        mat[i] = (int *)malloc(columns * sizeof(int));
        if (mat[i] == NULL)
            return false;
    }
    return true;
}

void print_m(int **mat, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}
