#include <stdio.h>

void print_inverted_string();

int main()
{
	print_inverted_string();
	printf("\n");

	return 0;
}

void print_inverted_string()
{
	char c = getchar();
	if (c == '\n')
		return;
	print_inverted_string();
	printf("%c", c);
}
