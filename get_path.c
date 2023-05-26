#include "shell.h"

/**
 * *get_path_var - gets the environment PATH variable
 * @env: Environment variable
 *
 * Return: the value of the PATH variable, NULL otherwise
 */
char *get_path_var(char **env) {
	int i = 0;

	if (env == NULL)
		return NULL;

	while (env[i] != NULL) {
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		/* skipping PATH= and returning the variable */

		i++;
	}

	return (NULL);  /* There is not path variable */
}

/**
 * *create_path - creates a new path to a file
 * @command_arg: The command/executable to check.
 * @path_dir: The directory to add to the file
 *
 * Description: Creates a new path to check using the stat()
 * function to be able to find the file
 * Return: the newly created path, NULL otherwise
 */
char *create_path(char *command_arg, char *path_dir)
{
	char *new_path;
	int path_len;

	if (command_arg == NULL || path_dir == NULL)
		return (NULL);

	path_len = strlen(command_arg) + strlen(path_dir) + 2;
	new_path = malloc(path_len * sizeof(char));
	if (new_path == NULL)
		return (NULL);

	strcpy(new_path, path_dir);
	strcat(new_path, "/");
	strcat(new_path, command_arg);

	return (new_path);
}

/**
 * *get_path - finds the path for a command/executable
 * @command_arg: The command/executable to find the path for
 * @env: The environment variable
 *
 * Return: The path where the file is, NULL otherwise
 */
char *get_path(char *command_arg, char **env)
{
	char *path_var, *cmd_path, **paths = NULL;
	int i = 0, path_count;
	struct stat file_stat;

	/* get the path variable */
	path_var = get_path_var(env);
	if (path_var == NULL || command_arg == NULL)
		return (NULL);
	/* if the command is correct, don't check */
	if (stat(command_arg, &file_stat) == 0)
		return (command_arg);
	/* get the paths using get_args() */
	path_count = count_args(path_var, ":");
	if (path_count == -1)
		return (NULL);
	paths = get_args(path_var, ":");
	if (paths == NULL)
		return (NULL);

	while (paths[i] != NULL)
	{
		cmd_path = create_path(command_arg, paths[i]);
		if (cmd_path == NULL)
			return (NULL);

		if (stat(cmd_path, &file_stat) == 0)
		{
			free_args(paths, path_count);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	/* don't forget to free cmd_path if returned*/
	free_args(paths, path_count);
	return (NULL);
}
