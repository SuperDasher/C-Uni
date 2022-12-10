#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	uint32_t amount;
	if (argc < 2)
	{
		printf("argomento non inserito,\nmostro i primi 50 numeri primi per default");
		amount = 50;
	}
	else
	{
		amount = atoi(argv[1]);
	}

	uint64_t current = 3, *prime;

	if (amount == 0)
	{
		return 0;
	}

	if (amount > 0)
	{
		prime = (uint64_t *)malloc(sizeof(uint64_t) * amount);
		if (prime == NULL)
		{
			perror("malloc() failed");
			exit(errno);
		}
		prime[0] = 2;
	}

	for (uint32_t i = 1; i < amount; i++)
	{
		bool is_prime = true;
		for (uint32_t j = 1; j < i; j++)
		{
			if (current / prime[j] < prime[j])
			{
				break;
			}
			if (current % prime[j] == 0)
			{
				is_prime = false;
				break;
			}
		}
		current += 2;
		if (!is_prime)
		{
			i--;
			continue;
		}
		prime[i] = current - 2;
	}

	// for (uint32_t i = 0; i < amount - 1; i++)
	// {
	// 	if (i % 5 == 0)
	// 	{
	// 		printf("\n");
	// 	}
	// 	printf("%" PRIu64 "\t\t\t", prime[i]);
	// }
	printf("%" PRIu64 "\n", prime[amount - 1]);
	free(prime);

	return 0;
}
