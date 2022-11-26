#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <custom/math.h>

int main()
{
	int numeratore1, denominatore1;
	int numeratore2, denominatore2;

	int result_num, result_den, result_mcd;

	do
	{
		printf("inserisci numeratore e denominatore della prima frazione (con denominatore diverso da 0):\n");
		scanf("%d%d", &numeratore1, &denominatore1);
	} while (denominatore1 == 0);

	do
	{
		printf("inserisci numeratore e denominatore della seconda frazione (con denominatore diverso da 0):\n");
		scanf("%d%d", &numeratore2, &denominatore2);
	} while (denominatore2 == 0);

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
