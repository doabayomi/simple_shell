#include "shell.h"

/**
 * count_args - counts the number of arguments in a string
 * @input: Input string
 * @delimiter: Seperating string
 *
 * Return: Number of arguments, -1 if NULL is given or something
 * fails.
 */
int count_args(char *input, char *delimiter)
{
	char *token, *string;
	int arg_count = 0;

	if (input == NULL || delimiter == NULL)
		return (-1);

	string = strdup(input);
	if (string == NULL)
		return (-1);

	token = strtok(string, delimiter);
	while (token != NULL)
	{
		arg_count++;
		token = strtok(NULL, delimiter);
	}

	free(string);
	return (arg_count);
}

/**
 * **get_args - gets the arguments in an input string.
 * @input: Input string
 * @delimiter: Seperating string
 *
 * Return: Number of arguments, NULL if input is NULL
 * or something fails.
 */
char **get_args(char *input, char *delimiter)
{
	char *token, *string, **args;
	int arg_count, ind;

	/* count_args() can confirm if it is NULL */
	arg_count = count_args(input, delimiter);
	if (arg_count == -1)
		return (NULL);

	args = malloc((arg_count + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);

	string = strdup(input);
	if (string == NULL)
	{
		free(args);
		return (NULL);
	}

	token = strtok(string, delimiter);
	for (ind = 0; ind < arg_count; ind++)
	{
		args[ind] = strdup(token);
		token = strtok(NULL, delimiter);
	}

	args[arg_count] = NULL;
	free(string);
	return (args);
}

/**
 * free_args - frees the argument array made by count_args
 * @args: Argument array
 * @arg_count: Number of arguments in array.
 */
void free_args(char **args, int arg_count)
{
	int j;

	for (j = 0; j < arg_count; j++)
		free(args[j]);

	free(args);
}
