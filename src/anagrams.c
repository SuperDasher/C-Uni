#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <custom/string.h>

#define STR_LEN 100

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "usage: %s <word> <word>", argv[0]);
		exit(EXIT_FAILURE);
	}
	char *str1 = argv[1];
	char *str2 = argv[2];
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if (!str_isalpha(str1) || !str_isalpha(str2))
	{
		fprintf(stderr, "error: only alphabetic characters are allowed");
		exit(EXIT_FAILURE);
	}
	if (len1 != len2)
	{
		printf("le parole %s e %s non sono anagrammi\n", str1, str2);
		return 0;
	}
	str_tolower(str1);
	str_tolower(str2);
	int count[26] = {0};
	for (int i = 0; i < len1; i++)
	{
		count[str1[i] - 'a']++;
		count[str2[i] - 'a']--;
	}
	for (int i = 0; i < 26; i++)
	{
		if (count[i] != 0)
		{
			printf("le parole %s e %s non sono anagrammi\n", str1, str2);
			return 0;
		}
	}
	printf("le parole %s e %s sono anagrammi\n", str1, str2);
}
