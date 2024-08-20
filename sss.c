#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
char *_getpath(const char *name)
{
	extern char **environ;
	int i;
	char *token, *str, *env_cpy;

	i = 0;
	while (environ[i])
	{
		env_cpy = strdup(environ[i]);
		token = strtok(env_cpy, "=");
		if (strcmp(token, name) == 0)
		{
			token = strtok(NULL, "=");
			str = strdup(token);
			free(env_cpy);
			return (str);
 		}
		free(env_cpy);
		i++;
	}
	return (NULL);
} 
char *findcommand(char *strcom, char **av)
{
	char *path, *token, *command;

	if (access(strcom, F_OK) == 0)
		return (strcom);
	path = _getpath("PATH");
	if (path)
	{
		token = strtok(path, ":");
		while (token)
		{
			command = malloc(sizeof(char) * (strlen(token) + 1 + strlen(strcom)));
			if (!command)
			{
				free(path);
				return (NULL);
			}

			strcpy(command, token);
			strcat(command, "/");
			strcat(command, strcom);
			
			if (access(command, F_OK) == 0)
			{
				free(path);
				return (command);
			}
			else
			{
				token = strtok(NULL, ":");
				free(command);
			}
		}
	free(path);
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
	char *token, *command, *buffer = NULL;

	while (1)
	{
		write(1, "$ ", 2);
		bytes_read = getline(&buffer, &n, stdin);
		if (bytes_read == -1)
		{
			printf("Bye\n");
			break;
		} else if (bytes_read == 1)
			continue;
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
				free(buffer);
				free(array);
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
			if (execve(command, array, env) == -1)
				printf("Error con execve\n");
		}
		else
			wait(&status);
		free(command);
		free(array);
	}
	free(buffer);
	return (0);
}
