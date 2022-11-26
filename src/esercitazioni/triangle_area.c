#include <stdio.h>
#include <stdlib.h>

int main()
{
	int base, height;
	printf("inserisci la base e l'altezza di un triangolo:\n");
	scanf("%d%d", &base, &height);

	if (base <= 0 || height <= 0)
	{
		fprintf(stderr, "errore:\n");
		if (base <= 0)
			fprintf(stderr, "base negativa\n");
		if (height <= 0)
			fprintf(stderr, "altezza negativa\n");
		exit(EXIT_FAILURE);
	}

	printf("l'area del triangolo e' %.1f\n", (float)base * height / 2);

	return 0;
}
