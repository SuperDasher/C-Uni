#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STR_LEN 101

int main()
{
	char string[STR_LEN];
	char substring[STR_LEN];

	printf("Inserisci la stringa:\n");
	fgets(string, STR_LEN, stdin);
	printf("Inserisci la sottostringa da sostituire:\n");
	fgets(substring, STR_LEN, stdin);

	string[strlen(string) - 1] = '\0';
	substring[strlen(substring) - 1] = '\0';

	for (int i = 0; string[i]; i++)
	{
		if (string[i] == substring[0])
		{
			bool found = true;
			for (int j = 0; substring[j] != '\0'; j++)
			{
				if (string[i + j] != substring[j])
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				for (int j = 0; substring[j]; j++)
				{
					string[i + j] = '*';
				}
			}
		}
	}

	printf("%s\n", string);

	return 0;
}
