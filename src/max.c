#include <stdio.h>

int main()
{
    int a, b;
    printf("inserisci due valori:\n");
    scanf("%d%d", &a, &b);

    if (a > b)
        printf("%d", a);
    else
        printf("%d", b);
    printf(" e' il valore piu' grande\n");

    return 0;
}