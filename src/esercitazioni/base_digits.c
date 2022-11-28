#include <stdio.h>
#include <stdlib.h>
#include <custom/string.h>

int count_base_digits(int, int);

int main(int argc, char *argv[])
{
	if (argc != 3 || !str_isuint(argv[1]) || !str_isuint(argv[2]))
	{
		fprintf(stderr, "Usage: %s <positive_integer> <positive_integer>", argv[0]);
		exit(EXIT_FAILURE);
	}
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);
	printf("%d\n", count_base_digits(n1, n2));

	return 0;
}

int count_base_digits(int n, int base)
{
	if (n < base)
		return 1;
	else
		return 1 + count_base_digits(n / base, base);
}
