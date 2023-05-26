#include "shell.h"

/**
 * handle_error - handles errors in function calls
 * @error: Error message
 * @args: Array from get_args()
 * @input: The return value of get_input();
 * @arg_count: The return value of arg_count
 */
void handle_error(char *error, char **args, char *input, int arg_count)
{
	perror(error);
	if (args != NULL || arg_count == -1)
	{
		free_args(args, arg_count);
	}
	if (input != NULL)
		free(input);
	exit(EXIT_FAILURE);
}

/**
 * exec_command - handles the execution of the input command
 * @args: Return from get_args()
 * @input: Return from get_input
 * @count: Return from count_args
 * @path: Where the return from get_path will be stored
 * @env: The current environment;
 */
void exec_command(char **args, char *input, int count, char *path, char **env)
{
	pid_t pid;
	int ret, status;

	pid = fork();
	if (pid == -1)
		handle_error("pid_error", args, input, count);
	else if (pid == 0)
	{
		path = get_path(args[0], env);
		if (path == NULL)
			handle_error("path failed", args, input, count);

		args[0] = path;
		ret = execve(args[0], args, env);
		if (ret == -1)
		{
			free(path);
			handle_error("exec failed", args, input, count);
		}
	}
	else
		wait(&status);
}

/**
 * handle_non_interactive - Handles the non interactive state
 * @env: environment variable
 */
void handle_non_interactive(char **env)
{
	char *input, **args, *cmd_path = NULL;
	int arg_count = 0;
	size_t bufsize = MAX_INPUT_SIZE;
	ssize_t read_count;

	input = malloc(bufsize);
	if (input == NULL)
		handle_error("malloc failed", NULL, NULL, -1);

	while ((read_count = getline(&input, &bufsize, stdin)) != -1)
	{
		if (input[0] == '\n')
			continue;

		input[read_count - 1] = '\0';

		arg_count = count_args(input, " \n");
		args = get_args(input, " \n");
		if (args == NULL)
			handle_error("get_args failed", NULL, input, -1);

		if (strcmp("exit", args[0]) == 0)
		{
			free_args(args, arg_count);
			free(input);
			exit(EXIT_SUCCESS);
		}

		exec_command(args, input, arg_count, cmd_path, env);
		free(cmd_path);
		free_args(args, arg_count);
	}

	free(input);
}

/**
 * main - The main shell container
 * @ac: The number of arguments
 * @av: The array of arguments
 * @env: The environment variable
 *
 * Return: 0
 */
int main(int ac, char **av, char *env[])
{
	char *input, **args, *cmd_path = NULL;
	int arg_count = 0, is_interactive = isatty(STDIN_FILENO);

	(void)ac;
	(void)av;
	if (is_interactive)
	{
		while (1)
		{
			write(STDOUT_FILENO, "$ ", 2);

			input = get_input();
			if (input[0] == '\n')
				continue;

			arg_count = count_args(input, " \n");
			args = get_args(input, " \n");
			if (args == NULL)
				handle_error("get_args", NULL, input, -1);
			/* handling the exit command */
			if (strcmp("exit", args[0]) == 0)
			{
				free_args(args, arg_count);
				free(input);
				exit(EXIT_SUCCESS);
			}

			exec_command(args, input, arg_count, cmd_path, env);
			free(cmd_path);
			free(input);
			free_args(args, arg_count);
		}
	}
	else
		handle_non_interactive(env);
	return (0);
}
