#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "mygetenv.c"
int findcommand(char *strcom, char **av)
{
	char *path, *token, *command;

	path = _getpath("PATH");
	printf("Path: %s\n", path);
	token = strtok(path, ":");
	while (token)
	{
		printf("token es: %s\n", token);
		token = strcat(token, "/");
		command = strcat(token, strcom);
		printf("command es: %s\n", command);
		if (execve(command, av, NULL) == -1)
			token = strtok(NULL, ":");
	}
	return (0);
}
/**
 * getenv - prints the environment
 *
 * Return: Always 0.
 */
int _getenv(int ac, char **av, char **env)
{
    unsigned int i;

    i = 0;
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}
/**
 * main - Super Simple Shell
 * Return: 1 Always Success
 */
int main(int ac, char **av, char **env)
{
	size_t n;
	char *buffer;
	int pid, status, i = 0, envb = 0;
	size_t bytes_read = 0;
	char **array;
	char *token;

	while (1)
	{
		write(1, "$ ", 2);
		bytes_read = getline(&buffer, &n, stdin);
		if (bytes_read == -1)
		{
			printf("Bye\n");
			break;
		}
		token = strtok(buffer, " \t\n");
		array = malloc(sizeof(char *) * 1024);
		if (!array)
			printf("Error de memoria\n");
		while (token)
		{
			array[i] = token;
			if (strcmp(token, "exit") == 0)
			{
				printf("Exiting...\n");
				return (0);
			}
			else if (strcmp(token, "env") == 0)
			{
				_getenv(ac, av, env);
				envb = 1;
			}
			token = strtok(NULL, " \t\n");
			i++;
		}
		if (envb == 1)
			continue;
		array[i] = NULL;
		i = 0;
		pid = fork();
		if (pid == -1)
			printf("Error con fork\n");
		if (pid == 0)
		{
			if (execve(array[0], array, NULL) == -1)
			{
				if (findcommand(array[0], array) == 0)
					printf("Error: Command not found");
			}
		}
		else
			wait(&status);
		free(array);
	}
	return (0);
}
