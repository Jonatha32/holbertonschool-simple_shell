#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv);
void execute_command(char *input);
void handle_error(char *command);
char *read_input(void);
char **parse_input(char *input);
void free_arguments(char **args);

#endif