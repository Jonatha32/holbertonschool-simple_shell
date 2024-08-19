#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_getenv(const char *name)
{
	extern char **environ;
	int i;
	char *token;

	i = 0;
	while (environ[i])
	{
		token = strtok(environ[i], "=");
		if (strcmp(token, name) == 0)
		{
			return (strtok(NULL, "="));
		}
		i++;
	}
}

void main(void)
{
	char *path = _getenv("PATH");
	char *token;

	token = strtok(path, ":");
	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}
}
