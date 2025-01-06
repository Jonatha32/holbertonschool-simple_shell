#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * find_comm - find command in PATH
 * @command: parameter
 * @path: path
 * Return: Full Path
 */

char *find_comm(char *command, char *path)
{
	char *copia_path = strdup(path);
	char *dirpath = strtok(copia_path, ":");
	char full_path[1024];
	char *resultado = NULL;

	while (dirpath != NULL)
	{
	snprintf(full_path, sizeof(full_path), "%s/%s", dirpath, command);
		if (access(full_path, X_OK) == 0)
		{
		resultado = strdup(full_path);
		break;
		}
		dirpath = strtok(NULL, ":");
	}
	free(copia_path);
	return (resultado);
}

/**
 * exe_com - tokenizes the input and execute
 * @line: input
 * @path: PATH Variable
 */

void exe_com(char *line, char *path)
{
	char *argumentos[100], *token; 
	char *full_path;
	int i = 0;

	token = strtok(line, " ");
	while (token != NULL && i < 99)
	{
	argumentos[i++] = token; 
	token = strtok(NULL, " ");
	}
	argumentos[i] = NULL; 
	full_path = find_comm(argumentos[0], path);
	if (full_path == NULL)
	{
		printf("%s: Command not found\n", argumentos[0]);
		return;
	}
	pid_t pid = fork();
			if (pid == 0)
			{
				execve(full_path, argumentos, environ);
				perror("Execution Failed");
				exit(EXIT_FAILURE);
			}
			else if (pid > 0)
			{
				wait(NULL);
			}
			else
			{
				perror("Fork Failed");
			}
	free(full_path);
}

/**
 * main - function
 * @argc: parameter
 * @argv: parameter
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	ssize_t bytes_read = 0;
	size_t len = 0;
	char *line = NULL, *path = getenv("PATH");

	if (path == NULL) 
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

