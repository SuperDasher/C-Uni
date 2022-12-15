#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define DECK_SIZE 52
#define EXTRACTED_CARDS 27
#define STACKS 3
#define CARDS_PER_STACK EXTRACTED_CARDS / STACKS

struct card
{
	char value;
	char seed;
};

void shuffle_deck(struct card[], size_t);
void mix_stacks(struct card[STACKS][CARDS_PER_STACK]);
void build_stacks(struct card[EXTRACTED_CARDS], struct card[STACKS][CARDS_PER_STACK]);
int print_stacks_and_ask(struct card[STACKS][CARDS_PER_STACK]);
void get_cards_from_stacks(struct card[EXTRACTED_CARDS], struct card[STACKS][CARDS_PER_STACK]);
size_t results_in_common(struct card **, struct card[CARDS_PER_STACK], size_t);

int main()
{
	srand(time(NULL));

	struct card deck[DECK_SIZE];
	FILE *file = fopen("src/files/input/mazzoPolimi.bin", "rb");
	if (file == NULL)
	{
		perror("Error opening file");
		exit(errno);
	}
	fread(deck, sizeof(struct card), DECK_SIZE, file);
	fclose(file);

	shuffle_deck(deck, DECK_SIZE);

	struct card extractedCards[EXTRACTED_CARDS];
	for (int i = 0; i < EXTRACTED_CARDS; i++)
	{
		extractedCards[i] = deck[i];
	}
	shuffle_deck(deck, EXTRACTED_CARDS);
	file = fopen("src/files/output/mazzoStudente.bin", "wb");
	if (file == NULL)
	{
		perror("Error opening file");
		exit(errno);
	}
	fwrite(extractedCards, sizeof(struct card), EXTRACTED_CARDS, file);
	fclose(file);

	printf("Carte estratte:\n");
	for (int i = 0; i < EXTRACTED_CARDS; i++)
	{
		printf("%c%c ", extractedCards[i].value, extractedCards[i].seed);
	}
	printf("\nMemorizza una carta e premi un pulsante per continuare");
	getch();

	struct card card_stacks[STACKS][CARDS_PER_STACK];
	struct card *result = malloc(CARDS_PER_STACK * sizeof(struct card));
	size_t possible_cards = CARDS_PER_STACK;
	if (result == NULL)
	{
		perror("malloc() failed");
		exit(errno);
	}
	build_stacks(deck, card_stacks);
	printf("\n");
	int stack_index = print_stacks_and_ask(card_stacks);
	memcpy(result, card_stacks[stack_index], CARDS_PER_STACK * sizeof(struct card));
	possible_cards = results_in_common(&result, card_stacks[stack_index], possible_cards);
	mix_stacks(card_stacks);
	get_cards_from_stacks(extractedCards, card_stacks);
	build_stacks(extractedCards, card_stacks);
	for (int i = 0; i < STACKS - 1; i++)
	{
		int stack_index = print_stacks_and_ask(card_stacks);
		possible_cards = results_in_common(&result, card_stacks[stack_index], possible_cards);
		mix_stacks(card_stacks);
		get_cards_from_stacks(extractedCards, card_stacks);
		build_stacks(extractedCards, card_stacks);
	}

	if (possible_cards != 1)
	{
		fprintf(stderr, "qualcosa e' andato storto...\n");
		exit(EXIT_FAILURE);
	}

	struct card found_card = result[0];
	free(result);
	int position = 0;
	for (int i = 0; i < EXTRACTED_CARDS; i++)
	{
		if (found_card.value == extractedCards[i].value && found_card.seed == extractedCards[i].seed)
		{
			position = i + 1;
			printf("|%c%c| ", extractedCards[i].value, extractedCards[i].seed);
			continue;
		}
		printf("%c%c ", extractedCards[i].value, extractedCards[i].seed);
	}
	printf("\nla tua carta e' la numero %d\n", position);

	return 0;
}

void shuffle_deck(struct card deck[], size_t cards_count)
{
	struct card temp;
	for (size_t i = 0; i < cards_count; i++)
	{
		int j = rand() % cards_count;
		temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}
}

void mix_stacks(struct card card_stacks[STACKS][CARDS_PER_STACK])
{
	struct card temp;
	for (int i = 0; i < STACKS; i++)
	{
		int j = rand() % STACKS;
		for (int k = 0; k < CARDS_PER_STACK; k++)
		{
			temp = card_stacks[i][k];
			card_stacks[i][k] = card_stacks[j][k];
			card_stacks[j][k] = temp;
		}
	}
}

void build_stacks(struct card deck[EXTRACTED_CARDS], struct card card_stacks[STACKS][CARDS_PER_STACK])
{
	for (int i = 0; i < CARDS_PER_STACK; i++)
		for (int j = 0; j < STACKS; j++)
			card_stacks[j][i] = deck[j + i * STACKS];
}

int print_stacks_and_ask(struct card card_stacks[STACKS][CARDS_PER_STACK])
{
	printf("1\t2\t3\n");
	for (int i = 0; i < CARDS_PER_STACK; i++)
	{
		for (int j = 0; j < STACKS; j++)
		{
			printf("%c%c\t", card_stacks[j][i].value, card_stacks[j][i].seed);
		}
		printf("\n");
	}
	printf("in quale pila si trova la tua carta? ");
	int stack_number;
	scanf("%d", &stack_number);
	while (stack_number < 1 || stack_number > 3)
	{
		printf("ci sono 3 pile. Seleziona una delle tre: ");
		scanf("%d", &stack_number);
	}
	return stack_number - 1;
}

void get_cards_from_stacks(struct card cards[EXTRACTED_CARDS], struct card card_stacks[STACKS][CARDS_PER_STACK])
{
	for (int i = 0; i < STACKS; i++)
		for (int j = 0; j < CARDS_PER_STACK; j++)
			cards[j + i * CARDS_PER_STACK] = card_stacks[i][j];
}

size_t results_in_common(struct card **dest, struct card stack[CARDS_PER_STACK], size_t dest_size)
{
	struct card *result = malloc(CARDS_PER_STACK * sizeof(struct card));
	if (result == NULL)
	{
		perror("malloc() failed");
		exit(errno);
	}
	int count = 0;
	for (size_t i = 0; i < dest_size; i++)
		for (int j = 0; j < CARDS_PER_STACK; j++)
			if ((*dest + i)->seed == stack[j].seed && (*dest + i)->value == stack[j].value)
				result[count++] = stack[j];
	*dest = realloc(result, count * sizeof(struct card));
	if (result == NULL)
	{
		perror("realloc() failed");
		exit(errno);
	}
	if (*dest == NULL)
	{
		perror("realloc() failed");
		exit(errno);
	}
	return count;
}
