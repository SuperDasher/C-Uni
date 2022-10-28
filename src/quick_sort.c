#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <array.h>

int compare(const void *, const void *);

int main(int argc, char *argv[])
{
	argv++;
	argc--;

	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <number> <number> <number> ...\n", argv[-1]);
		exit(EXIT_FAILURE);
	}

	int *numbers = malloc(argc * sizeof(int));
	if (numbers == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	printf("array di parametri prima del sort:\n[");
	for (int i = 0; i < argc - 1; i++)
	{
		numbers[i] = atoi(argv[i]);
		printf("%d, ", numbers[i]);
	}
	numbers[argc - 1] = atoi(argv[argc - 1]);
	printf("%d]\n", numbers[argc - 1]);

	qsort((void *)numbers, (size_t)argc, sizeof(int), compare);

	printf("\narray di parametri dopo il sort:\n");
	print_a(numbers, argc);
	free(numbers);

	return 0;
}

int compare(const void *arg1, const void *arg2)
{
	return *(int *)arg1 - *(int *)arg2;
}
