#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <custom/datastruct.h>
#include <custom/intsort.h>

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
		perror("malloc() failed");
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

	quick_sort(numbers, 0, argc - 1);

	printf("\narray di parametri dopo il sort:\n");
	print_a(numbers, argc);
	free(numbers);

	return 0;
}
