#include <stdio.h>
#include <utils/string.h>
#include <stdbool.h>

#define STR_LEN 101

int main()
{
	char string[STR_LEN];
	char substring[STR_LEN];

	printf("Inserisci la stringa:\n");
	inputstring(string, STR_LEN);
	printf("Inserisci la sottostringa da sostituire:\n");
	inputstring(substring, STR_LEN);

	for (int i = 0; string[i]; i++)
	{
		if (string[i] != substring[0])
			continue;
		bool found = true;
		for (int j = 0; substring[j]; j++)
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

	printf("%s\n", string);

	return 0;
}
