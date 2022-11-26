#include <stdio.h>

int main()
{
	int number;

	printf("inserisci numeri finche' non inserisci 0 o un numero negativo\n");
	scanf("%d", &number);
	int max = number;
	int min = number;
	int sum = 0;
	int count = 0;

	while (number > 0)
	{
		if (number > max)
		{
			max = number;
		}
		if (number < min)
		{
			min = number;
		}
		sum += number;
		count++;
		scanf("%d", &number);
	}
	if (count == 0)
	{
		printf("nessun numero inserito\n");
		return 0;
	}
	// deepcode ignore DivisionByZero: guard clause already checks if count is 0 and ends the program prematurely
	float med = (float)sum / count;
	printf("\nmassimo: %d\n", max);
	printf("minimo: %d\n", min);
	printf("media: %.2f\n", med);
	return 0;
}
