#include <stdio.h>

int main()
{
	int n;
	printf("inserisci un numero:\n");
	scanf("%d", &n);

	if (n == 0)
	{
		printf("uguale a 0\n");
		return 0;
	}
	if (n == 100)
	{
		printf("uguale a 100\n");
		return 0;
	}
	if (n < 0)
	{
		printf("negativo\n");
		return 0;
	}
	if (n < 100)
	{
		printf("fra 0 e 100\n");
		return 0;
	}
	printf("maggiore di 100\n");

	return 0;
}
