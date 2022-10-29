#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <array.h>

int main()
{
	struct point
	{
		float x;
		float y;
	};
	int n;
	struct point *polygon;

	printf("Quanti lati ha il poligono? ");
	scanf("%d", &n);
	if (n < 3)
	{
		fprintf(stderr, "Il poligono deve avere almeno 3 lati\n");
		exit(EXIT_FAILURE);
	}
	polygon = malloc(n * sizeof(struct point));
	if (polygon == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}

	for (int i = 0; i < n; i++)
	{
		printf("Inserisci le coordinate del vertice %d: ", i + 1);
		scanf("%f%f", &polygon[i].x, &polygon[i].y);
	}

	float perimeter = 0;
	for (int i = 0; i < n; i++)
	{
		int next_i = (i + 1) % n;
		perimeter += sqrt(pow(polygon[i].x - polygon[next_i].x, 2) + pow(polygon[i].y - polygon[next_i].y, 2));
	}

	printf("Il perimetro del poligono e' %f\n", perimeter);

	return 0;
}
