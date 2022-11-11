#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

void inputstring(char str[], int len)
{
	fflush(stdin);
	fgets(str, len, stdin);
	fflush(stdin);
	if (str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
}

void inputstring_dynamic(char **str, int len)
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

void str_tolower(char *str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 'a' - 'A';
	}
}

void str_toupper(char *str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 'a' - 'A';
	}
}

bool str_isalpha(char *str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
			return false;
	}
	return true;
}

bool str_isalpha_lower(char *str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] < 'a' || str[i] > 'z')
			return false;
	}
	return true;
}

bool str_isalpha_upper(char *str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] < 'A' || str[i] > 'Z')
			return false;
	}
	return true;
}

bool str_isuint(char *str)
{
	int len = strlen(str);
	if (len == 0)
		return false;
	for (int i = 0; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

bool str_isnegint(char *str)
{
	int len = strlen(str);
	if (len == 0)
		return false;
	if (str[0] != '-')
		return false;
	for (int i = 1; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

bool str_isint(char *str)
{
	return str_isuint(str) || str_isnegint(str);
}
