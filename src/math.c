#include <custom/math.h>
#include <custom/string.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <first_number> <second_number>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (!is_number(argv[1]) || !is_number(argv[2]))
	{
		fprintf(stderr, "Error: Invalid number(s) provided.\n");
		exit(EXIT_FAILURE);
	}

	int first_number = atoi(argv[1]);
	int second_number = atoi(argv[2]);

	printf("%d^%d = %d\n", first_number, second_number, power(first_number, second_number));
	printf("L'MCD fra %d e %d e': %d", first_number, second_number, mcd(first_number, second_number));

	return 0;
}
