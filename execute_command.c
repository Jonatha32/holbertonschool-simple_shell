#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 *
 *
 *
 */

void execute_command(char *line)
{
	char *argv[2];
	pid_t pid;

	argv[0] = line;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork Error");
		return;
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("./simple_shell");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
