#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void check_command(char *command)
{
	if (access(command, F_OK) == 0)
		printf("%s: FOUND THE FILE\n", command);
	else
		printf("%s: FILE DOESNT EXIST\n", command);
}
int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	char *token;

	while (1)
	{
		write(1, "$ ", 2);
		getline(&buffer, &buffer_size, stdin);
		token = strtok(buffer, " \t\n");
		if (strcmp(token, "_which") == 0)
		{
			token = strtok(NULL, " \t\n");
			while (token)
			{
				check_command(token);
				token = strtok(NULL, " \t\n");
			}
		}
		else
		{
			write(1, "Command doesn't exist\n", 22);
		}
	}
	return (0);
}
