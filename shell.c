#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
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
 * main - Main shell container
 * @ac: No of arguments
 * @av: Argument list
 * @env: Environment variable of program.
 *
 * Return: 0
 */
int main(int ac, char *av[], char *env[])
{
	char *input, *command;
	char **input_args;
	int has_path, status, ret = 0;
	pid_t pid;

	while (1)
	{
		input = get_command();
		if (input == '\n')
			continue; /* handling only new line input */

		if (input == EOF) /* Checking end of file condition */
			exit(EXIT_SUCCESS);

		/**
		 * The string is first broken by space using get_args and then
		 * first checked alongside builtins and also along whether the
		 * command is valid before calling fork.
		 */
		input_args = get_args(input, " "); /* splitting the input */
		ret = get_builtin(argv[0])(); /* builtins checked */
		if (ret == -1)
			handle_cmd_error(input_args, input);

		pid = fork();
		if (pid == -1) /* Error in pid */
			handle_cmd_error(input_args, input);
		else if (pid == 0)
		{
			/* Child process */
			command = get_path(input_args[0]);
			if (command == NULL)
				handle_cmd_error(input_args, input);

			input_args[0] = command;
			/* Run command */
			execve(input_args[0], input_args, NULL);
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
