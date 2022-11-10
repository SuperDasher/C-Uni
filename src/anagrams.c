#include <stdio.h>
#include <utils/string.h>

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
	for (int i = 0; i < len1; i++)
	{
		if ((str1[i] < 'a' || str1[i] > 'z') && (str1[i] < 'A' || str1[i] > 'Z'))
		{
			fprintf(stderr, "the first word must contain only letters\n");
			exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < len2; i++)
	{
		if ((str2[i] < 'a' || str2[i] > 'z') && (str2[i] < 'A' || str2[i] > 'Z'))
		{
			fprintf(stderr, "the second word must contain only letters\n");
			exit(EXIT_FAILURE);
		}
	}
	if (len1 != len2)
	{
		printf("le parole %s e %s non sono anagrammi\n", str1, str2);
		return 0;
	}
	for (int i = 0; i < len1; i++)
	{
		if (str1[i] >= 'A' && str1[i] <= 'Z')
			str1[i] += 'a' - 'A';
		if (str2[i] >= 'A' && str2[i] <= 'Z')
			str2[i] += 'a' - 'A';
	}
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