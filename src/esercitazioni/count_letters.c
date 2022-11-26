#include <stdio.h>
#include <string.h>
#include <custom/string.h>

#define STR_LEN 101
#define ALPHABET_LETTERS 26

int main()
{
	char string[STR_LEN];
	printf("inserisci una stringa con lunghezza massima 100:\n");
	inputstring(string, STR_LEN);

	int count[ALPHABET_LETTERS] = {0};

	printf("lettera\tcodice ASCII\n");
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] >= 'a' && string[i] <= 'z')
		{
			count[string[i] - 'a']++;
		}
		else if (string[i] >= 'A' && string[i] <= 'Z')
		{
			count[string[i] - 'A']++;
		}
		printf("'%c'\t%d\n", string[i], string[i]);
	}

	printf("\noccorrenze lettere:\n");
	for (int i = 0; i < ALPHABET_LETTERS; i++)
	{
		if (count[i] > 0)
		{
			printf("%c: %d\n", i + 'a', count[i]);
		}
	}

	return 0;
}
