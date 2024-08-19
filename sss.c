#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
char *_getpath(const char *name)
{
	extern char **environ;
	int i;
	char *token, *str;

	i = 0;
	while (environ[i])
	{
		token = strtok(environ[i], "=");
		if (strcmp(token, name) == 0)
		{
			token = strtok(NULL, "=");
			str = malloc(sizeof(char) * (strlen(token) + 1));
			str = strdup(token);
			return (str);
 		}
		i++;
	}
	return (NULL);
} 
char *findcommand(char *strcom, char **av)
{
	char *path, *token, *command;

	path = _getpath("PATH");
	printf("PATH es %s\n", path);
	if (path)
	{
		token = strtok(path, ":");
		while (token)
		{
			command = malloc(sizeof(char) * (strlen(token) + 1 + strlen(strcom)));
			if (!command)
				return (NULL);


			command = strdup(token);
			command = strcat(command, "/");
			command = strcat(command, strcom);

			if (access(command, F_OK) == 0)
				return (command);
			else
			{
				token = strtok(NULL, ":");
				free(command);
			}
		}
	}
	return (NULL);
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
	size_t n, bytes_read = 0;
	int pid, status, i = 0, envb = 0;
	char **array;
	char *token, *command, *buffer;

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
		{
			free(array);
			continue;
		}
		array[i] = NULL;
		i = 0;
		command = findcommand(array[0], array);
		printf("Command es: %s\n", command);
		if (!command)
		{
			printf("Error: Command not found\n");
			free(array);
			continue;
		}
		pid = fork();
		if (pid == -1)
			printf("Error con fork\n");
		if (pid == 0)
		{
			if (execve(command, array, NULL) == -1)
				printf("Error con execve\n");
		}
		else
			wait(&status);
		free(array);
	}
	return (0);
}
