#include <stdbool.h>

#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

void inputstring(char str[], int len);

void inputstring_dynamic(char **str, int len);

void str_tolower(char *str);

void str_toupper(char *str);

bool str_isalpha(char *str);

bool str_isalpha_lower(char *str);

bool str_isalpha_upper(char *str);

bool str_isuint(char *str);

bool str_isnegint(char *str);

bool str_isint(char *str);

#endif /* CUSTOM_STRING_H */
