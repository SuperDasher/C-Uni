#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DATE_LEN 20

struct date
{
	int day;
	int month;
	int year;
	int hours;
	int minutes;
};
struct date_minutes
{
	int value;
	int leap_amount;
	bool includes_skipped_days;
};
bool valid_date(char *, struct date *);
bool is_number(char *, size_t);
struct date_minutes date_to_minutes(struct date);
struct date minutes_to_date(int);

int main()
{
	char date_s1[DATE_LEN] = { 0 };
	char date_s2[DATE_LEN] = { 0 };
	
	struct date date1;
	struct date date2;
	
	printf("inserisci una prima data in formato DD-MM-YYYY hh:mm :\n");
	fgets(date_s1, DATE_LEN, stdin);

	while (!valid_date(date_s1, &date1))
	{
		printf("formato errato, reinserire con formato DD-MM-YYYY hh:mm :\n");
		fgets(date_s1, DATE_LEN, stdin);
	}

	printf("inserisci una seconda data in formato DD-MM-YYYY hh:mm :\n");
	fgets(date_s2, DATE_LEN, stdin);

	while (!valid_date(date_s2, &date2))
	{
		printf("formato errato, reinserire con formato DD-MM-YYYY hh:mm :\n");
		fgets(date_s2, DATE_LEN, stdin);
	}

	// TODO: calculate the time difference

	return 0;
}

bool valid_date(char *date_s, struct date *date)
{
	if (date_s[2] != '-' || date_s[5] != '-' || date_s[10] != ' ' || date_s[13] != ':' || date_s[16] != '\n')
	{
		return false;
	}
	char day_s[3];
	char month_s[3];
	char year_s[5];
	char hours_s[3];
	char minutes_s[3];

	strncpy(day_s, date_s, 2);
	strncpy(month_s, date_s + 3, 2);
	strncpy(year_s, date_s + 6, 4);
	strncpy(hours_s, date_s + 11, 2);
	strncpy(minutes_s, date_s + 14, 2);

	struct date dt;

	dt.day = atoi(day_s);
	dt.month = atoi(month_s);
	if (!is_number(year_s) || !is_number(hours_s) || !is_number(minutes_s))
	{
		return false;
	}
	dt.year = atoi(year_s);
	dt.hours = atoi(hours_s);
	dt.minutes = atoi(minutes_s);

	if (dt.year < 0 || dt.month < 1 || dt.month > 12  || dt.day < 1)
	{
		return false;
	}

	if (dt.hours < 0 || dt.hours > 24 || dt.minutes < 0 || dt.minutes > 59)
	{
		return false;
	}

	if (dt.year == 1582 && dt.month == 10)
	{
		if ((dt.day > 4 && dt.day < 16) || dt.day > 30)
		{
			return false;
		}
		*date = dt;
		return true;
	}
	
	if (dt.month == 2)
	{
		if (dt.day > 29)
		{
			return false;
		}
		if (dt.year % 4 != 0 || dt.year % 100 == 0)
		{
			if (dt.day > 28)
			{
				return false;
			}
		}
		*date = dt;
		return true;
	}
	switch (dt.month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (dt.day > 31)
			{
				return false;
			}
			*date = dt;
			return true;
		default:
			if (dt.day > 30)
			{
				return false;
			}
			*date = dt;
			return true;
	}
}

bool is_number(char * str, size_t len)
{
	if (len == 1)
	{
		return str[0] >= '0' && str[0] <= '9'
	}
	if (str[0] < '0' || str[0] > '9' || str[0] != '-')
	{
		return false;
	}
	for (int i = 1; i < len; i++)
	{
		if (str[0] < '0' || str[0])
		{
			return false;
		}
	}
	return true;
}

struct date_minutes date_to_minutes(struct date date)
{
	struct date_minutes result = { date.minutes, 0, false };
	result.value += date.hour * 60;
	result.value += date.day * 60 * 24;
	// TODO: finish function
	if ()
}

struct date minutes_to_date(int minutes)
{

}
