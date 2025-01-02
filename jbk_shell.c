#include "shell.h"

/**
 * read_input - Reads a line of input from the user
 *
 * Return: Pointer to the input string
 */

char *read_input(void)
{
	char *input = NULL;
	size_t len = 0;
	
	if (getline(&input, &len, stdin) == -1)
	{
		return NULL;
	}

	return input;
}

/**
 * execute_command - Executes a command
 * @input: Command input
 */

void execute_command(char *input)
{
        pid_t pid;
        int status;
        char *command = strtok(input, "\n");

        if (command == NULL || strlen(command) == 0)
        {
                return;
        }

        pid = fork();
        if (pid == -1)
        {
                perror("fork");
                return;
        }

        if (pid == 0)
        {
                char *argv[2];
		argv[0] = command;
		argv[1] = NULL;

                if (execve(command, argv, NULL) == -1)
                {
                        fprintf(stderr, "./jbk_shell: No such file or directory\n");
                        exit(EXIT_FAILURE);
                }
        }
        else
        {
                wait(&status);
        }
}
