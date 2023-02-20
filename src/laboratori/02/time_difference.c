#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <custom/string.h>

#define DATE_LEN 20

struct date
{
	int day;
	int month;
	int year;
	int hours;
	int minutes;
};
void ask_date(struct date *, char *, char *);
bool is_valid_date(char *, struct date *);
bool is_leap_year(int);
bool are_equal_dates(struct date, struct date);
bool are_sorted_dates(struct date, struct date);
void sort_date(struct date *, struct date *);
void swap_date(struct date *, struct date *);
struct date date_difference(struct date, struct date);

int main()
{
	struct date date1;
	struct date date2;
	struct date difference;

	ask_date(&date1, "inserisci la data di partenza in formato [DD-MM-YYYY hh:mm]\n", "formato errato, reinserire con formato [DD-MM-YYYY hh:mm]\n");
	ask_date(&date2, "inserisci la data di arrivo in formato [DD-MM-YYYY hh:mm]\n", "formato errato, reinserire con formato [DD-MM-YYYY hh:mm]\n");

	if (are_equal_dates(date1, date2))
	{
		printf("Non hai viaggiato nel tempo...\n");
		return 0;
	}

	difference = date_difference(date1, date2);

	char *time_direction = are_sorted_dates(date1, date2) ? "futuro" : "passato";
	char *year = difference.year == 1 ? "anno" : "anni";
	char *month = difference.month == 1 ? "mese" : "mesi";
	char *day = difference.day == 1 ? "giorno" : "giorni";
	char *hours = difference.hours == 1 ? "ora" : "ore";
	char *minutes = difference.minutes == 1 ? "minuto" : "minuti";

	printf("Grande Giove! Hai viaggiato nel %s di %d %s, %d %s, %d %s, %d %s e %d %s!\n",
		   time_direction,
		   difference.year, year,
		   difference.month, month,
		   difference.day, day,
		   difference.hours, hours,
		   difference.minutes, minutes);

	return 0;
}

void ask_date(struct date *date, char *prompt, char *invalid_prompt)
{
	char date_s[DATE_LEN] = {1};

	printf("%s", prompt);
	inputstring(date_s, DATE_LEN);

	while (!is_valid_date(date_s, date))
	{
		printf("%s", invalid_prompt);
		inputstring(date_s, DATE_LEN);
	}
}

bool is_valid_date(char *date_s, struct date *date)
{
	if (date_s[2] != '-' || date_s[5] != '-' || date_s[10] != ' ' || date_s[13] != ':' || date_s[16] != '\0')
	{
		return false;
	}
	char day_s[3] = {0};
	char month_s[3] = {0};
	char year_s[5] = {0};
	char hours_s[3] = {0};
	char minutes_s[3] = {0};

	strncpy(day_s, date_s, 2);
	strncpy(month_s, date_s + 3, 2);
	strncpy(year_s, date_s + 6, 4);
	strncpy(hours_s, date_s + 11, 2);
	strncpy(minutes_s, date_s + 14, 2);

	struct date dt;

	dt.day = atoi(day_s);
	dt.month = atoi(month_s);
	if (!str_isuint(year_s) || !str_isuint(hours_s) || !str_isuint(minutes_s))
	{
		return false;
	}
	dt.year = atoi(year_s);
	dt.hours = strcmp(hours_s, "24") == 0 ? 0 : atoi(hours_s);
	dt.minutes = atoi(minutes_s);

	if (dt.year < 1888 || dt.year > 2100 || dt.month < 1 || dt.month > 12 || dt.day < 1)
	{
		return false;
	}

	if (dt.hours < 0 || dt.hours > 24 || dt.minutes < 0 || dt.minutes > 59)
	{
		return false;
	}

	if (dt.month == 2)
	{
		if (dt.day > 29)
		{
			return false;
		}
		if (!is_leap_year(dt.year))
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

bool is_leap_year(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

bool are_equal_dates(struct date date1, struct date date2)
{
	return date1.year == date2.year &&
		   date1.month == date2.month &&
		   date1.day == date2.day &&
		   date1.hours == date2.hours &&
		   date1.minutes == date2.minutes;
}

bool are_sorted_dates(struct date date1, struct date date2)
{
	if (date1.year > date2.year)
	{
		return false;
	}
	if (date1.year == date2.year &&
		date1.month > date2.month)
	{
		return false;
	}
	if (date1.year == date2.year &&
		date1.month == date2.month &&
		date1.day > date2.day)
	{
		return false;
	}
	if (date1.year == date2.year &&
		date1.month == date2.month &&
		date1.day == date2.day &&
		date1.hours > date2.hours)
	{
		return false;
	}
	if (date1.year == date2.year &&
		date1.month == date2.month &&
		date1.day == date2.day &&
		date1.hours == date2.hours &&
		date1.minutes > date2.minutes)
	{
		return false;
	}
	return true;
}

void sort_date(struct date *date1, struct date *date2)
{
	if (!are_sorted_dates(*date1, *date2))
	{
		swap_date(date1, date2);
	}
}

void swap_date(struct date *date1, struct date *date2)
{
	struct date temp = *date1;
	*date1 = *date2;
	*date2 = temp;
}
struct date date_difference(struct date date_minuend, struct date date_subtrahend)
{
	sort_date(&date_subtrahend, &date_minuend);
	bool day_borrowed = false;
	bool month_borrowed = false;
	struct date difference = {0};
	if (date_subtrahend.minutes > date_minuend.minutes)
	{
		date_minuend.minutes += 60;
		date_minuend.hours--;
	}
	difference.minutes = date_minuend.minutes - date_subtrahend.minutes;
	if (date_subtrahend.hours > date_minuend.hours)
	{
		day_borrowed = true;
		date_minuend.hours += 24;
		date_minuend.day--;
	}
	difference.hours = date_minuend.hours - date_subtrahend.hours;
	if (date_subtrahend.day > date_minuend.day)
	{
		month_borrowed = true;
		if (date_minuend.month == 3)
		{
			if (is_leap_year(date_minuend.year))
			{
				date_minuend.day += 29;
			}
			else
			{
				date_minuend.day += 28;
			}
		}
		else
		{
			switch (date_minuend.month)
			{
			case 1:
			case 2:
			case 4:
			case 6:
			case 8:
			case 9:
			case 11:
				date_minuend.day += 31;
				break;
			default:
				date_minuend.day += 30;
				break;
			}
		}
		date_minuend.month--;
	}
	difference.day = date_minuend.day - date_subtrahend.day;
	if (difference.day <= 0 && month_borrowed)
	{
		if (day_borrowed)
		{
			difference.day = 0;
		}
		else
		{
			difference.day = 1;
		}
	}
	if (date_subtrahend.month > date_minuend.month)
	{
		date_minuend.month += 12;
		date_minuend.year--;
	}
	difference.month = date_minuend.month - date_subtrahend.month;
	difference.year = date_minuend.year - date_subtrahend.year;
	return difference;
}
