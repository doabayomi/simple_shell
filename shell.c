#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "shell.h"

int main(int ac, char *av[], char *env[])
{
	char *input, *path, *command;
	char **input_args;
	int has_path;
	pid_t pid;

	while (1)
	{
		is_interactive_mode = isatty(STDIN_FILENO);
		if (is_interactive_mode)
			input = get_command();
		if (input == '\n')
			continue;

		input_args = get_args(input, " ");
		has_path = count_args(input_args[0], "/");
		if ((has_path > 1) && (stat(input_args[0], &file_stat) != 0))
		{
			free_variables();
			print_command_error();
		}

		pid = fork();
		if (pid == -1)
		{
			free_variables(input_arg, input);
			print_fork_error();
		}
		else if (pid == 0)
		{
			command = get_path(input_args[0]);
			if (command == NULL)
			{
				free_variables(input_args, input);
				print_command_error();
			}
			input_args[0] = command;
			execve(input_args[0], input_args, NULL);
	}
}
