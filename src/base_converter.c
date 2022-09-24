#include <stdio.h>

int main()
{
	int number;

	printf("inserisci un numero\n");
	scanf("%d", &number);

	int result_2 = 0;
	int result_8 = 0;

	int n = number;
	int power = 1;
	while (n > 0)
	{
		result_2 += power * (n % 2);
		n /= 2;
		power *= 10;
	}
	n = number;
	power = 1;
	while (n > 0)
	{
		result_8 += power * (n % 8);
		n /= 8;
		power *= 10;
	}

	printf("il numero in base 2 e' %d\n", result_2);
	printf("il numero in base 8 e' %d\n", result_8);

	return 0;
}
