#include <stdio.h>
#include <stdlib.h>

int compare(const void *, const void *);

int main(int argc, char *argv[])
{
    argv++;
    argc--;

    if (argc < 2)
    {
        printf("usage: %s <number> <number> <number> ...\n", argv[-1]);
        return 1;
    }

    int *numbers = malloc(argc * sizeof(int));
    printf("array di parametri prima del sort:\n{");
    for (int i = 0; i < argc - 1; i++)
    {
        numbers[i] = atoi(argv[i]);
        printf("%d, ", numbers[i]);
    }
    numbers[argc - 1] = atoi(argv[argc - 1]);
    printf("%d}\n", numbers[argc - 1]);

    qsort((void *)numbers, (size_t)argc, sizeof(int), compare);

    printf("\narray di parametri dopo il sort:\n{");
    for (int i = 0; i < argc - 1; i++)
    {
        printf("%d, ", numbers[i]);
    }
    printf("%d}\n", numbers[argc - 1]);
    free(numbers);

    return 0;
}

int compare(const void *arg1, const void *arg2)
{
    return *(int *)arg1 - *(int *)arg2;
}
