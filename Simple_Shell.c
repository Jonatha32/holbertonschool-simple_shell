#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 *
 *
 */

int main(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t bytes_read;

	while (1)
	{
		printf("#Simple_Shell$ ");

		bytes_read = getline(&line, &bufsize, stdin);
		if (bytes_read == -1)
		{
			if (feof(stdin))
			{
				printf("Exiting Shell...\n");
				break;
			}
			perror("Getline Error");
			continue;
		}

		line[strcspn(line, "\n")] = '\0';

		execute_command(line);
	}
	free(line);
	line = NULL;
	return (0);
}
