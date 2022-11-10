// do the eratosthenes

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define N 100

int main()
{
	bool prime[N + 1];
	for (int i = 0; i <= N; i++)
		prime[i] = true;

	for (int i = 2; i <= sqrt(N); i++)
	{
		if (prime[i])
		{
			for (int j = i * i; j <= N; j += i)
				prime[j] = false;
		}
	}

	printf("i numeri primi minori o uguali a %d sono:\n", N);
	for (int i = 2; i <= N; i++)
	{
		if (prime[i])
			printf("%d ", i);
	}
	printf("\n");

	return 0;
}
