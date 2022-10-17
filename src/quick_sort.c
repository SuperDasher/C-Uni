#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
	if (numbers == NULL)
	{
		// FIXME: add error message for negative numbers
		printf("out of memory\n");
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

	print_a(numbers, argc, "\narray di parametri dopo il sort:\n");
	free(numbers);

	return 0;
}

int compare(const void *arg1, const void *arg2)
{
	return *(int *)arg1 - *(int *)arg2;
}
