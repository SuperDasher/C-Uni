// create a program that calculates the resulting score you get depending from the combo knowing that the formula for it in math terms is:
//score =  sum of i = 1 to combo(10 + floor(i * .5))
// example: if combo is 6 (considering that floor rounds up down to the nearest integer down)
// score = 10 + 11 + 11 + 12 + 12 + 13 = 69

#include <stdio.h>
#include <math.h>

int main(void)
{
	int combo;
	int score = 0;
	int i;
	printf("Enter combo: ");
	scanf("%d", &combo);
	for (i = 1; i <= combo; i++)
	{
		score += 10 + floor(i * .5);
	}
	printf("Score: %d\n", score);
}