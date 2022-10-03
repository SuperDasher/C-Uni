#include <stdio.h>
#include <stdlib.h>

int compare(const void *, const void *);

int main(int argc, char *argv[])
{
    argv++;
    argc--;

    printf("array di parametri prima del sort:\n[");
    for (int i = 0; i < argc - 1; i++)
    {
        argv[i] = atoi(argv[i]);
        printf("%d, ", argv[i]);
    }
    printf("%d]\n", argv[argc - 1]);

    qsort((void *)argv, (size_t)argc, sizeof(int *), compare);
    
    printf("\narray di parametri dopo del sort:\n");
    for (int i = 0; i < argc - 1; i++)
    {
        printf("%d, ", argv[i]);
    }
    printf("%d]\n", argv[argc - 1]);

    return 0;
}

int compare(const void * arg1, const void * arg2)
{
    return (*(int *)arg1 - *(int *)arg2);
}