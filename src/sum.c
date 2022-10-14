#include <stdio.h>

int main()
{
	int q, r;
	float y = 0;

	printf("inserire q ed r per l'equazione `y = SUM(i = q to r) (1 / i)`\n");
	printf("q: ");
	scanf("%d", &q);
	printf("r: ");
	scanf("%d", &r);

	if (q > r)
	{
		int temp = q;
		q = r;
		r = temp;
		printf("\ni valori sono stati invertiti poiche' non sono stati inseriti correttamente\n");
	}

	for (int i = q; i <= r; i++)
	{
		y += 1.0 / i;
	}

	printf("\ny = %f\n", y);

	return 0;
}
