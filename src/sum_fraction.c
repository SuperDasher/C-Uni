#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int mcd(int, int);

int mcm(int, int);

int main()
{
    int numeratore1, denominatore1;
    int numeratore2, denominatore2;

    int result_num, result_den, result_mcd;

    printf("inserisci numeratore e denominatore della prima frazione:\n");
    scanf("%d%d", &numeratore1, &denominatore1);

    printf("inserisci numeratore e denominatore della seconda frazione:\n");
    scanf("%d%d", &numeratore2, &denominatore2);

    result_den = mcm(denominatore1, denominatore2);
    numeratore1 *= result_den / denominatore1;
    numeratore2 *= result_den / denominatore2;
    result_num = numeratore1 + numeratore2;
    result_mcd = mcd(result_num, result_den);

    printf("la somma fra le due frazioni e' %d", result_num / result_mcd);
    if (result_den != result_mcd)
    {
        printf("/%d", result_den / result_mcd);
    }
    printf("\n");

    return 0;
}

int mcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    while (a != b)
    {
        (a > b) ? (a -= b) : (b -= a);
    }
    return a;
}

int mcm(int a, int b)
{
    a = abs(a);
    b = abs(b);
    return a * b / mcd(a, b);
}