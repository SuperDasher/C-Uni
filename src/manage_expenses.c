#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MIN_CHARS_BACK 300
#define STEP_BACK 4
#define MONTH_CHARS 10
#define YEAR_CHARS 5
#define MONTH_YEAR_CHARS 16

void check_file(FILE *file);
void seek_last_month(FILE *file);
void get_month_year(char month_year[MONTH_YEAR_CHARS]);
void get_file_month_year(FILE *file, char month_year[MONTH_YEAR_CHARS]);

int main(int argc, char *argv[])
{
	FILE *file = fopen("money.md", "r+");
	check_file(file);
	
	char cur_month_year[MONTH_YEAR_CHARS];
	get_month_year(cur_month_year);

	char file_month_year[MONTH_YEAR_CHARS];
	get_file_month_year(file, file_month_year);

	if (strcmp(file_month_year, cur_month_year) != 0)
	{
		// TODO: Add months to file until current month
	}
	// TODO: Create options and logic to different operations

	fclose(file);
	return 0;
}

/**
 * @brief Check if there are errors trying to open the file
 * 
 * @param file 
 */
void check_file(FILE *file)
{
	if (file == NULL)
	{
		if (errno == ENOENT)
		{
			printf("File money.md does not exist\n");
			exit(errno);
		}
		if (errno == EACCES)
		{
			printf("File money.md is not accessible\n");
			exit(errno);
		}
		printf("Error opening file money.md\n");
		exit(errno);
	}
}

/**
 * @brief Puts the cursor in front of the last month in money.md
 * 
 * @param file 
 */
void seek_last_month(FILE *file)
{
	fseek(file, -MIN_CHARS_BACK, SEEK_END);
	while (fgetc(file) != '#')
	{
		fseek(file, -STEP_BACK, SEEK_CUR);
	}
	while (fgetc(file) != ' ')
		;
}

/**
 * @brief Get the current month year string
 */
void get_month_year(char month_year[MONTH_YEAR_CHARS])
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	char month[MONTH_CHARS];
	char year[YEAR_CHARS];

	strftime(month, MONTH_CHARS, "%B", &tm);
	strftime(year, YEAR_CHARS, "%Y", &tm);

	strncpy(month_year, month, MONTH_CHARS);
	strcat(month_year, " ");
	strncat(month_year, year, YEAR_CHARS);
}

/**
 * @brief Get the month year string from the file
 * 
 * @param file
 * @param month_year 
 */
void get_file_month_year(FILE *file, char month_year[MONTH_YEAR_CHARS])
{
	seek_last_month(file);
	fgets(month_year, MONTH_YEAR_CHARS, file);
	month_year[strlen(month_year) - 1] = '\0';
}
