#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

bool malloc_m(int ***, int, int);
void free_m(int ***, int);
void print_m(int **, int, int);

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
        printf("out of memory\n");
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
    print_m(a, n, m);
    printf("prima matrice:\n");
    print_m(b, n, m);
    printf("somma:\n");
    print_m(result, n, m);

    free_m(&a, n);
    free_m(&b, n);
    free_m(&result, n);

    return 0;
}

bool malloc_m(int ***mat, int rows, int columns)
{
    *mat = (int **)malloc(rows * sizeof(int *));
    if (*mat == NULL)
        return false;
    for (int i = 0; i < rows; i++)
    {
        *(*mat + i) = (int *)malloc(columns * sizeof(int));
        if (*(*mat + i) == NULL)
            return false;
    }
    return true;
}

void free_m(int ***mat, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(*(*mat + i));
    }
    free(*mat);
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
