#include <stdio.h>

void convert(int, int);

int main()
{
	int number;

	printf("inserisci un numero\n");
	scanf("%d", &number);

	convert(number, 2);
	convert(number, 8);

	return 0;
}

void convert(int number, int base)
{
	if (base > 10)
	{
		printf("non posso convertire in base %d\n", base);
		return;
	}
	int n = number;
	long long int result = 0;
	long long int power = 1;
	while (n > 0)
	{
		result += power * (n % base);
		n /= base;
		power *= 10;
	}
	printf("%d in base %d e' %lld\n", number, base, result);
}