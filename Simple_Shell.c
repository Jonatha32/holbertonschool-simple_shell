#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

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
	char *line = NULL, *path = getenv("PATH");

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
			perror("Read Line Error");
			break;
		}

		line[strcspn(line, "\n")] = '\0';
		if (strcmp(line, "exit") == 0)
			break;
		exe_com(line, path);
	}
	free(line);
	return (0);
}

