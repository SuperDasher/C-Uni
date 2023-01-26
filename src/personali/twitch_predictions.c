#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	size_t options;
	size_t *options_points;
	size_t total_points = 0;
	size_t selected_option;
	size_t selected_total_points;
	size_t selected_partial_points;
	float selected_points_percentage;
	size_t possible_gain;

	printf("How many options are available? ");
	scanf("%zu", &options);
	while (options < 2)
	{
		printf("There must be at least 2 options. Please select a valid amount of options: ");
		scanf("%zu", &options);
	}

	options_points = (size_t *)malloc(options * sizeof(size_t));
	if (options_points == NULL)
	{
		perror("Error! memory not allocated");
		exit(errno);
	}

	for (size_t i = 0; i < options; i++)
	{
		printf("How many points does option %zu have? ", i + 1);
		scanf("%zu", &options_points[i]);
		total_points += options_points[i];
	}

	char continue_option;
	do
	{
		printf("Which option did you select? ");
		scanf("%zu", &selected_option);
		while (selected_option < 1 || selected_option > options)
		{
			printf("Invalid option. Please select a valid option: ");
			scanf("%zu", &selected_option);
		}

		selected_total_points = options_points[selected_option - 1];

		printf("How many points did you bet? ");
		scanf("%zu", &selected_partial_points);
		while (selected_partial_points > selected_total_points)
		{
			printf("You can't bet more points than the option has. Please select a valid amount of points: ");
			scanf("%zu", &selected_partial_points);
		}

		selected_points_percentage = (float)selected_partial_points / (float)selected_total_points;
		possible_gain = round((selected_points_percentage * total_points)) - selected_partial_points;

		printf("\ngiven the amount of points you bet:\n\t");
		printf("you can win %zu points\n\t", possible_gain + selected_partial_points);
		printf("getting your %zu points back\n\t", selected_partial_points);
		printf("and %zu points more\n\t", possible_gain);
		printf("getting %.2f%% of the total %zu points spent in the bet by everyone.\n\t", selected_points_percentage * 100, total_points);
		printf("This means everyone else that selected this same option would win %zu points collectively\n\n", total_points - (possible_gain + selected_partial_points));

		printf("Do you want to continue with another person's choice? (Y/n) ");

		fflush(stdin);
		continue_option = getchar();
		fflush(stdin);
	} while (continue_option == 'y' || continue_option == 'Y');

	return 0;
}
