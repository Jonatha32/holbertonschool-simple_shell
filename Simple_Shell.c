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
	char *copia_path = strdup(path); /* duplicamos PATH */
	char *dirpath = strtok(copia_path, ":"); /* Separamos en directorios*/
	char full_path[1024]; /* Donde almacenaremos la ruta del comando */
	char *resultado = NULL; /* Resultado que pasaremos a execute_command */

	while (dirpath != NULL)
	{
	snprintf(full_path, sizeof(full_path), "%s/%s", dirpath, command);
			/* creamos la ruta con el formato "dirpath/command" */
		if (access(full_path, X_OK) == 0) /* Si existe y es ejecutable */
		{
		resultado = strdup(full_path); /* duplicamos y almacenamos el resultado */
		break;
		}
		dirpath = strtok(NULL, ":"); /* pasamos al siguiente token */
	}
	free(copia_path);
	return (resultado);
}

/**
 * exe_com - tokenizes the input and execute
 * @line: input
 * @path: PATH Variable
 */

void exe_com(char *line, char *path)
{
	char *argumentos[100], *token; /*variables para los argumentos que se pasan*/
	char *full_path; /*Ruta Completa */
	int i = 0;

	token = strtok(line, " ");
	/*Dividimos la linea mediante " " para tratar cada palabra individualmente */
	while (token != NULL && i < 99)
	{
	argumentos[i++] = token; /*Los tokens se almacenan en la variable argumentos*/
	token = strtok(NULL, " "); /* Pasa al siguiente token */
	}
	argumentos[i] = NULL; /*Al final se agrega el NULL para terminar el string*/
	full_path = find_comm(argumentos[0], path);
	/*Se llama a la funcion find_command y se almacena el resultado en full_path*/
	if (full_path == NULL) /* se trata el caso de que full_path sea NULL */
	{
		printf("%s: Command not found\n", argumentos[0]);
		return;
	}
	pid_t pid = fork(); /* Creamos un proceso */
			if (pid == 0) /* Proceso hijo que ejecute el comando */
			{
				execve(full_path, argumentos, environ);
				perror("Execution Failed");
				exit(EXIT_FAILURE);
			}
			else if (pid > 0) /* Proceso Padre, que espera al hijo */
			{
				wait(NULL);
			}
			else /* Error al crear el proceso */
			{
				perror("Fork Failed");
			}
	free(full_path);
}

/**
 * main - function
 * @argc: parameter
 * @argv: parameter
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	ssize_t bytes_read = 0;
	size_t len = 0;
	char *line = NULL, *path = getenv("PATH");

	if (path == NULL) /* Si PATH es NULL */
	{
		perror("Failed to get PATH");
		return (1);
	}

	while (1)
	{
		printf("Simple_Shell$ "); /*Se muestra el prompt */
		bytes_read = getline(&line, &len, stdin); /* Usamos getline */
		if (bytes_read == -1) /* Caso Error getline */
		{
			perror("Read Line Error");
			break;
		}

		line[strcspn(line, "\n")] = '\0'; /* Eliminamos el posible salto de linea */
		if (strcmp(line, "exit") == 0) /* Por si escribe "Exit" */
			break;
		exe_com(line, path); /* Llamamos a exe_comm */
	}
	free(line);
	return (0);
}

