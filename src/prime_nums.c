#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    uint32_t amount;
    uint64_t current = 3, *prime;

    printf("quanti numeri primi vuoi elencare?\n");
    scanf("%u", &amount);

    if (amount == 0)
    {
        return 0;
    }

    if (amount > 0)
    {
        prime = (uint64_t *) malloc(sizeof(uint64_t) * amount);
        if (prime == NULL)
        {
            printf("out of memory\n");
            exit(1);
        }
        prime[0] = 1;
    }

    if (amount > 1)
    {
        prime[1] = 2;
    }

    for (uint32_t i = 2; i < amount; i++)
    {
        int8_t is_prime = 0;
        for (uint32_t j = 2; j < i; j++)
        {
            if (current / prime[j] < prime[j])
            {
                break;
            }
            if (current % prime[j] == 0)
            {
                is_prime = -1;
                break;
            }
        }
        current += 2;
        if (is_prime == -1)
        {
            i--;
            continue;
        }
        prime[i] = current - 2;
    }

    for (uint32_t i = 0; i < amount - 1; i++)
    {
        if (i % 5 == 0)
        {
            printf("\n");
        }
        printf("%lu, ", prime[i]);
    }
    printf("%lu\n", prime[amount - 1]);

    return 0;
}