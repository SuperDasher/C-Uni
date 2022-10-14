#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_CHARS_BACK 351
#define STEP_BACK 3

int main(int argc, char *argv[])
{
	FILE *fptr = fopen("money.md", "a+");
	fseek(fptr, -MIN_CHARS_BACK, SEEK_END);
	while (fgetc(fptr) != '#')
	{
		fseek(fptr, -STEP_BACK, SEEK_CUR);
	}
	
	fclose(fptr);
	return 0;
}
