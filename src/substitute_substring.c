#include <stdio.h>
#include <utils/string.h>
#include <stdbool.h>

#define STR_LEN 101

int main()
{
	char string[STR_LEN];
	char substring[STR_LEN];

	printf("Inserisci la stringa:\n");
	getstring(string, STR_LEN);
	printf("Inserisci la sottostringa da sostituire:\n");
	getstring(substring, STR_LEN);

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
