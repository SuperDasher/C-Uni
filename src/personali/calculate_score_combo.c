#include <stdio.h>
#include <math.h>
#include <stdbool.h>

unsigned long score_from_combo(unsigned combo);
unsigned combo_required_for_score(unsigned long score);

int main()
{
	printf("0 to end program\n");
	printf("-1 to switch\n");
	bool score_to_combo = false;
	long input = 0;
	do
	{
		char *prompt = score_to_combo ? "Score needed: " : "Combo: ";
		printf("%s", prompt);
		scanf("%ld", &input);
		if (input <= 0)
		{
			if (input == -1)
			{
				score_to_combo = !score_to_combo;
			}
			continue;
		}
		if (score_to_combo)
		{
			unsigned combo = combo_required_for_score((unsigned long)input);
			printf("Minimum combo: %u (%lu points)\n", combo, score_from_combo(combo));
		}
		else
		{
			unsigned long score = score_from_combo((unsigned)input);
			printf("Score: %lu\n", score);
		}
	} while (input != 0);
}

unsigned long score_from_combo(unsigned combo)
{
	unsigned long score = 0;
	for (unsigned i = 1; i <= combo; i++)
	{
		score += 10 + floor(i * .5);
	}
	return score;
}

unsigned combo_required_for_score(unsigned long score)
{
	unsigned combo = 0;
	unsigned long score_temp = 0;
	while (score_temp < score)
	{
		combo++;
		score_temp += 10 + floor(combo * .5);
	}
	return combo;
}
