#include <stdio.h>
#include <stdlib.h>
#include <utils/string.h>
#include <time.h>

#define RESULTS 11
#define DICE_SIDES 6

int main(int argc, char *argv[])
{
	srand(time(NULL));

	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <number of throws>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int throws = atoi(argv[1]);
	if (throws < 1 || !str_isuint(argv[1]))
	{
		fprintf(stderr, "number of throws must be a valid number greater than 0\n");
		exit(EXIT_FAILURE);
	}

	int count[RESULTS] = {0};
	for (int i = 0; i < (throws > 0 && str_isuint(argv[1])) ? throws : 0; i++)
	{
		int dice1 = rand() % DICE_SIDES + 1;
		int dice2 = rand() % DICE_SIDES + 1;
		int sum = dice1 + dice2;
		count[sum - 2]++;
	}
	int expected[RESULTS] = {0};
	for (int i = 0; i < DICE_SIDES; i++)
	{
		for (int j = 0; j < DICE_SIDES; j++)
		{
			expected[i + j]++;
		}
	}
	printf("\nsomma\toccorrenze\t%% aspettativa\t%% effettiva\n");
	for (int i = 0; i < RESULTS; i++)
	{
		printf("%5d\t%10d\t%10.2f%%\t%8.2f%%\n", i + 2, count[i], (float)expected[i] * 100 / (DICE_SIDES * DICE_SIDES), (float)count[i] * 100 / throws);
	}

	return 0;
}
