#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <custom/string.h>

#define NAME_MAX 20
#define MAX_INGREDIENTS 100

struct ingredient
{
	char name[NAME_MAX];
	int quantity;
};

bool check_ingredients(FILE *, FILE *);

int main()
{
	char recipe_name[NAME_MAX];
	printf("quale ricetta vuoi cucinare? (pasta, tiramisu)\n");
	inputstring(recipe_name, NAME_MAX);
	char recipe_path[NAME_MAX + 30] = "src/files/input/ricette/";
	strcat_s(recipe_path, NAME_MAX + 30 - 1, recipe_name);
	strcat_s(recipe_path, NAME_MAX + 30 - 1, ".txt");
	FILE *recipe = fopen(recipe_path, "r");
	if (recipe == NULL)
	{
		fprintf(stderr, "Non esiste nessuna ricetta con il nome: %s\n", recipe_name);
		exit(EXIT_FAILURE);
	}
	FILE *pantry = fopen("src/files/input/ricette/dispensa.txt", "r");
	if (pantry == NULL)
	{
		perror("Errore nell'apertura del file");
		exit(errno);
	}
	if (check_ingredients(pantry, recipe))
		printf("Si puo' cucinare la ricetta\n");
	else
		printf("Non si puo' cucinare la ricetta\n");
	fclose(pantry);
	fclose(recipe);

	return 0;
}

bool check_ingredients(FILE *pantry, FILE *recipe)
{
	struct ingredient pantry_ingredients[MAX_INGREDIENTS];
	struct ingredient recipe_ingredients[MAX_INGREDIENTS];
	int pantry_count = 0;
	int recipe_count = 0;

	while (fscanf(pantry, "%s %d", pantry_ingredients[pantry_count].name, &pantry_ingredients[pantry_count].quantity) != EOF && pantry_count < MAX_INGREDIENTS)
		pantry_count++;
	while (fscanf(recipe, "%s %d", recipe_ingredients[recipe_count].name, &recipe_ingredients[recipe_count].quantity) != EOF && recipe_count < MAX_INGREDIENTS)
		recipe_count++;

	bool every_ingredient = true;
	for (int i = 0; i < recipe_count; i++)
	{
		bool found = false;
		for (int j = 0; j < pantry_count; j++)
		{
			if (strcmp(recipe_ingredients[i].name, pantry_ingredients[j].name) == 0)
			{
				found = true;
				if (recipe_ingredients[i].quantity > pantry_ingredients[j].quantity)
				{
					every_ingredient = false;
					printf("%s : %d mancante\n", recipe_ingredients[i].name, recipe_ingredients[i].quantity - pantry_ingredients[j].quantity);
					break;
				}
				printf("%s : OK\n", recipe_ingredients[i].name);
				break;
			}
		}
		if (!found)
		{
			every_ingredient = false;
			printf("%s : %d mancante\n", recipe_ingredients[i].name, recipe_ingredients[i].quantity);
		}
	}
	return every_ingredient;
}
