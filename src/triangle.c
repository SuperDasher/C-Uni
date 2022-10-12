#include <stdio.h>

int main()
{
    int a, b, c;

    printf("inserisci tre misure per i lati di un triangolo\n");
    scanf("%d%d%d", &a, &b, &c);

    if (a >= b + c ||
        b >= a + c ||
        c >= b + c)
    {
        printf("i lati non possono appartenere a un triangolo\n");
        return 0;
    }

    if (a != b &&
        b != c &&
        a != c)
    {
        printf("il triangolo e' scaleno\n");
        return 0;
    }

    if (a == b && b == c)
    {
        printf("il triangolo e' equilatero\n");
        return 0;
    }

    printf("il triangolo e' isoscele\n");
    
    return 0;
}
