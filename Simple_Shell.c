#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

extern char **environ;

/**
 * get_env_value - Gets the value of an environment variable.
 * @name: The name of the variable.
 * Return: The value of the variable.
 */

char *get_env_value(const char *name)
{
	char *entrada, *valor;
	size_t len = strlen(name);
	int i = 0;

	while (environ[i] != NULL)
	{
		entrada = environ[i];
		if (strncmp(entrada, name, len) == 0 && entrada[len] == '=')
		{
			valor = entrada + len + 1;
			return (valor);
		}
		i++;
	}
	return (NULL);
}

/**
 * main - function
 * @argc: parameter
 * @argv: parameter
 * Return: Always 0
 */
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	ssize_t bytes_read = 0;
	size_t len = 0;
	char *line = NULL, *path = get_env_value("PATH");

	if (path == NULL)
	{
		perror("Failed to get PATH");
		return (1);
	}

	while (1)
	{
		printf("Simple_Shell$ ");
		bytes_read = getline(&line, &len, stdin);
		if (bytes_read == -1)
		{
			if (feof(stdin))
				break;
			perror("getline");
			continue;
		}

		line[strcspn(line, "\n")] = '\0';
		if (strcmp(line, "exit") == 0)
			break;
		exe_com(line, path);
	}
	free(line);
	return (0);
}

