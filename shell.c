#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * handle_cmd_error - handles the errors in main shell container.
 * @args: Argument list to be freed.
 * @input: input from get_command to be freed
 */
void handle_cmd_error(char **args, char *input)
{
	free(args); /* freeing return value of get_args */
	free(input); /* freeing return value of get_command */
	perror("./hsh: ");
	exit(EXIT_FAILURE);
}

/**
 * free_all - frees all the variables uses
 * @args: From get_args
 * @input: From get_command
 * @path: From get_path
 */
void free_all(char **args, char *input, char *path)
{
	if (args != NULL)
		free(args);
	if (input != NULL)
		free(input);
	if (path != NULL)
		free(path);
}

/**
 * run_command - performs execution on command
 * @input_args: return from get_args
 * @input: Input string
 * @command: Command to be made
 */
void run_command(char **input_args, char *input, char *command)
{
	command = get_path(input_args[0], env);
	if (command == NULL)
		handle_cmd_error(input_args, input);

	input_args[0] = command; /* changing args */

	/* Run command */
	execve(input_args[0], input_args, NULL);
	free_all(input_args, input, command);
	perror("./hsh");
	exit(EXIT_FAILURE);
}

/**
 * main - Main shell container
 * @ac: No of arguments
 * @av: Argument list
 * @env: Environment variable of program.
 *
 * Return: 0
 */
int main(int ac, char *av[] __attribute__((unused)), char *env[])
{
	char *input = NULL, *command = NULL, **input_args = NULL;
	int status, ret = 0;
	pid_t pid;
	int (*builtin_func)(void);

	(void)ac;
	while (1)
	{
		input = get_command();
		if (input[0] == '\0')
			continue;
		if (input == NULL) /* Checking NULL condition */
			exit(EXIT_SUCCESS);

		input_args = get_args(input, " "); /* splitting the input */
		builtin_func = get_builtin(input_args[0]); /* builtins checked */
		if (builtin_func != NULL)
		{
			ret = builtin_func();
			if (ret == -1)
				handle_cmd_error(input_args, input);
		}

		pid = fork();
		if (pid == -1) /* Error in pid */
			handle_cmd_error(input_args, input);
		else if (pid == 0)
			run_command(input_args, input, command);
		else
			wait(&status);
		free_all(input_args, input, command);
	}
	return (0);
}
