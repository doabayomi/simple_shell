#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "shell.h"

/**
 * *get_path_var - gets the PATH variable from the environment array
 * @env: The environment array
 *
 * Return: The PATH variable of the environment array.
 * NULL if something fails.
*/
char *get_path_var(char **env)
{
	int i = 0;
	char *var_name, *path;

	for (; env[i] != NULL; i++)
	{
		var_name = get_env_var(env[i], 0);
		if (_strcmp(var_name, "PATH") == 0)
		{
			free(var_name);
			path = get_env_var(env[i], 1);
			return (path);
		}

		free(var_name);
	}
	/**
	 * NOTE: Remember to pass the env variable in the form
	 * char *env[] and not char **env.
	*/
	return (NULL);
}


/**
 * *construct_new_path - makes a new path for a command
 * @command_arg: The command whose path is being created for
 * @path_dir: The directory to make the command path for
 *
 * Return: Newly constructed path. NULL if something fails
*/
char *construct_new_path(char *command_arg, char *path_dir)
{
	char *new_path;
	int path_len;

	path_len = strlen(command_arg) + strlen(path_dir) + 2;
	new_path = malloc(path_len * sizeof(char));
	if (new_path == NULL)
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}

	strcpy(new_path, path_dir);
	strcat(new_path, "/");
	strcat(new_path, command_arg);

	return (new_path);
}

/**
 * *get_path - finds the path of a command
 * @command_arg: Command to find path for
 * @env: The environment variable
 *
 * Return: The path of the command.
*/
char *get_path(char *command_arg, char **env)
{
	char *env_path_var, *cmd_path;
	char **paths = NULL;
	int i = 0;
	struct stat file_stat;

	if (stat(command_arg, &file_stat) == 0)
		return (command_arg);

	env_path_var = get_path_var(env);
	if (env_path_var == NULL)
		return (NULL);

	paths = get_args(env_path_var, ":");
	if (paths == NULL)
		return (NULL);

	while (paths[i] != NULL)
	{
		cmd_path = construct_new_path(command_arg, paths[i]);
		if (stat(cmd_path, &file_stat) == 0)
		{
			free(env_path_var);
			free(paths);
			return (cmd_path);
		}

		free(cmd_path);
		i++;
	}

	free(env_path_var);
	free(paths);
	return (NULL);
}
