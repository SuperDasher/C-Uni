#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getstring(char str[], int len)
{
	fflush(stdin);
	fgets(str, len, stdin);
	fflush(stdin);
	if (str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
}

void getstring_dynamic(char **str, int len)
{
	fflush(stdin);
	*str = (char *)malloc(len * sizeof(char));
	if (*str == NULL)
	{
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		exit(errno);
	}
	fgets(*str, len, stdin);
	fflush(stdin);
	if ((*str)[strlen(*str) - 1] == '\n')
		(*str)[strlen(*str) - 1] = '\0';
}