#include <stdio.h>

int main()
{
    int number, times;

    printf("inserisci due numeri\n");
    scanf("%d%d", &number, &times);

    if (times < 0)
    {
        number = -number;
        times = -times;
    }

    int result = 0;

    for (int i = 0; i < times; i++)
    {
        result += number;
    }

    printf("il prodotto e' %d\n", result);

    return 0;
}