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

	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

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

