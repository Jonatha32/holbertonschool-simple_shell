#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
/**
 * _getpath - Gets the String of the PATH
 * @name: Name of Environment Variable to look for
 * Return: String
 */
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
/**
 * findcommand - Finds the path of the command to execute
 * @strcom: Path or command to execute
 * Return: String of path of command
 */
char *findcommand(char *strcom)
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
 * @env: Environment Variables
 * Return: Always 0.
 */
int _getenv(char **env)
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
 * @ac: Count of Arguments
 * @av: Array of String Arguments
 * @env: Environment Variables
 * Return: 1 Always Success
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	size_t n, bytes_read = 0, eof = -1, ljump = 1;
	int pid, status, i = 0, envb = 0;
	char **array;
	char *token, *command, *buffer = NULL;

	while (1)
	{
		write(1, "$ ", 2);
		bytes_read = getline(&buffer, &n, stdin);
		if (bytes_read == eof)
		{
			printf("Bye\n");
			break;
		} else if (bytes_read == ljump)
			continue;
		token = strtok(buffer, " \t\n");
		array = malloc(sizeof(char *) * 1024);
		if (!array)
		{
			printf("Error de memoria\n");
			break;
		}
		while (token)
		{
			array[i] = token;
			if (strcmp(token, "exit") == 0)
			{
				printf("Exiting...\n");
				break;
			}
			else if (strcmp(token, "env") == 0)
			{
				_getenv(env);
				envb = 1;
			}
			token = strtok(NULL, " \t\n");
			i++;
		}

		if (strcmp(array[0], "exit") == 0)
		{
			free(array);
			break;
		}
		if (envb == 1)
		{
			free(array);
			continue;
		}
		array[i] = NULL;
		i = 0;
		command = findcommand(array[0]);
		if (!command)
		{
			perror(av[0]);
			free(array);
			continue;
		}
		pid = fork();
		if (pid == -1)
			perror(av[0]);
		if (pid == 0)
		{
			if (execve(command, array, env) == -1)
				perror(av[0]);
		}
		else
			wait(&status);
		if (command != array[0])
			free(command);
		free(array);
	}
	free(buffer);
	return (0);
}
