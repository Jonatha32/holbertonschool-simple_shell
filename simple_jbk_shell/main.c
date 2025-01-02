#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * Return: 0 on success
 */

int main(void)
{
	char *input;
	
	while (1)
	{
		printf("#jbk$ ");
		input = read_input();

		if (input == NULL)
		{
			free(input);
			break;
		}
		
		execute_command(input);
		free(input);
	}
	
	return (0);
}