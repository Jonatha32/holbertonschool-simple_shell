#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

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
