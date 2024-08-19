#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
/**
 * main - Super Simple Shell
 * Return: 1 Always Success
 */

int main(void)
{
	size_t n;
	char *buffer;
	int pid, status, i = 0;
	size_t bytes_read = 0;
	char **array;
	char *token;

	while (1)
	{
		write(1, "$ ", 2);
		bytes_read = getline(&buffer, &n, stdin);
		if (bytes_read == -1)
			printf("Error de lectura\n");
		token = strtok(buffer, " \t\n");
		array = malloc(sizeof(char *) * 1024);
		if (!array)
			printf("Error de memoria\n");
		while (token)
		{
			array[i] = token;
			token = strtok(NULL, " \t\n");
			i++;
		}
		array[i] = NULL;
		i = 0;
		pid = fork();
		if (pid == -1)
			printf("Error con fork\n");
		if (pid == 0)
		{
			if (execve(array[0], array, NULL) == -1)
				printf("Error con execve\n");
		}
		else
		{
			wait(&status);
		}
		free(array);
	}
	return (0);
}
