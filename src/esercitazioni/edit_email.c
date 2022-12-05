#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *edit_email(char *);

int main()
{
	char *original_email = "manupicc02@gmail.com";
	char *edited_email = edit_email(original_email);
	printf("original email: %s\n", original_email);
	printf("edited email: %s\n", edited_email);
	free(edited_email);

	return 0;
}

char *edit_email(char *email)
{
	char *edited_email;
	int new_email_length = strlen(email) + 1;
	for (int i = 0; i < strlen(email); i++)
	{
		if (email[i] == '.')
			new_email_length += 4;
		if (email[i] == '@')
			new_email_length += 3;
	}
	edited_email = (char *)calloc(new_email_length, sizeof(char));
	if (edited_email == NULL)
	{
		perror("calloc() failed");
		exit(errno);
	}
	for (int i = 0; i < strlen(email); i++)
	{
		if (email[i] == '.')
		{
			strncat(edited_email, "_dot_", 6);
			continue;
		}
		if (email[i] == '@')
		{
			strncat(edited_email, "_at_", 5);
			continue;
		}
		strncat(edited_email, &email[i], 1);
	}
	return edited_email;
}
