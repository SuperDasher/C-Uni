#include <stdio.h>
#include <utils/string.h>
#include <stdbool.h>

#define STR_LEN 501

int main()
{
	char str[STR_LEN];

	printf("inserisci una stringa con soli '[' e ']'\nverra' determinato se appartiene al linguaggio di Dyck (%d caratteri massimi)\n", STR_LEN - 1);
	inputstring(str, STR_LEN);

	int count = 0;
	bool isValidDyck = true;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '[')
			count++;
		else if (str[i] == ']')
			count--;
		else
		{
			printf("la stringa non appartiene al linguaggio di Dyck\n[carattere non valido: '%c']\n", str[i]);
			return 0;
		}
		if (count < 0)
			isValidDyck = false;
	}
	if (count == 0 && isValidDyck)
	{
		printf("la stringa appartiene al linguaggio di Dyck\n");
		return 0;
	}
	printf("la stringa non appartiene al linguaggio di Dyck\n");

	return 0;
}
