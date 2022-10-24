#include <stdio.h>

#define DAYS 7
#define TEMPERATURE_LOW_LIMIT 35
#define TEMPERATURE_HIGH_LIMIT 42

void draw_histogram(float *, int);
void draw_vertical_histogram(float *, int);

int main()
{
	float temperature[DAYS];
	printf("Inserisci le temperature del paziente:\n");
	for (int i = 0; i < 7; i++)
	{
		do
		{
			printf("Giorno %d: ", i + 1);
			scanf("%f", &temperature[i]);
		} while (temperature[i] < TEMPERATURE_LOW_LIMIT || temperature[i] >= TEMPERATURE_HIGH_LIMIT + 1);
	}

	printf("\n");
	draw_histogram(temperature, DAYS);
	printf("\n");
	draw_vertical_histogram(temperature, DAYS);

	float sum = 0;
	float max = temperature[0];
	float min = temperature[0];
	float average = 0;
	for (int i = 0; i < 7; i++)
	{
		if (temperature[i] > max)
		{
			max = temperature[i];
		}
		if (temperature[i] < min)
		{
			min = temperature[i];
		}
		sum += temperature[i];
	}
	average = sum / 7;

	printf("\nLa temperatura media e': %.1f\n\n", average);

	printf("La temperatura massima e': %.1f\n", max);
	printf("La temperatura minima e': %.1f\n", min);
	return 0;
}

void draw_histogram(float *temperature, int days)
{
	printf("GIORNO\tVALORE\tISTOGRAMMA\n");
	for (int i = 0; i < days; i++)
	{
		printf("     %d\t  %.1f\t", i + 1, temperature[i]);
		for (int j = TEMPERATURE_LOW_LIMIT; j <= temperature[i]; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}

void draw_vertical_histogram(float *temperature, int days)
{
	printf("ISTOGRAMMA VERTICALE\n");
	for (int i = TEMPERATURE_HIGH_LIMIT; i >= TEMPERATURE_LOW_LIMIT; i--)
	{
		printf("%d\t", i);
		for (int j = 0; j < days; j++)
		{
			if (temperature[j] >= i)
			{
				printf("*\t");
			}
			else
			{
				printf("\t");
			}
		}
		printf("\n");
	}
	printf("Giorno\t");
	for (int i = 1; i <= days; i++)
	{
		printf("%d\t", i);
	}
	printf("\n");
}
