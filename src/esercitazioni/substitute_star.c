#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *substitute_star(char *, char *);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <string> <string>", argv[0]);
		exit(EXIT_FAILURE);
	}
	char *result = substitute_star(argv[1], argv[2]);
	printf("%s\n", result);
	free(result);

	return 0;
}

char *substitute_star(char *dest_str, char *sub_str)
{
	int dest_len = strlen(dest_str);
	int sub_len = strlen(sub_str);
	int n_stars = 0;
	for (int i = 0; i < dest_len; i++)
	{
		if (dest_str[i] == '*')
			n_stars++;
	}
	if (n_stars == 0)
		return dest_str;
	int result_len = dest_len + sub_len * (n_stars - 1);
	char *result_str = (char *)calloc(result_len + 1, sizeof(char));
	if (result_str == NULL)
	{
		perror("malloc() failed");
		exit(errno);
	}
	int shift = 0;
	for (int i = 0; i < dest_len; i++)
	{
		if (dest_str[i] == '*')
		{
			for (int j = 0; j < sub_len; j++)
			{
				result_str[i + shift] = sub_str[j];
			}
			shift += sub_len - 1;
		}
		else
		{
			result_str[i + shift] = dest_str[i];
		}
	}
	return result_str;
}
