#include <stdio.h>
#include <string.h>

#define STR_LEN 101
#define ALPHABET_LETTERS 26

int main()
{
	char string[STR_LEN];
	printf("inserisci una stringa con lunghezza massima 100 (newline incluso):\n");
	fgets(string, STR_LEN - 1, stdin);

	int count[ALPHABET_LETTERS];
	// TODO: finish code

	return 0;
}
