#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * count_args - counts args in command for get_args() function
 * @command: Input command string
 * @delimiter: Splitting character (most likely space)
 *
 * Return: Number of words (arguments) in input string command.
*/
int count_args(char *command, char *delimiter)
{
	char *token, *tmp_copy;
	int count = 1; /*count is 1 because we have called token before loop */

	/* Why would pass NULL on this function? Do you even know how to code? */
	if (command == NULL || delimiter == NULL)
		return (-1);

	/* Have to use strdup cause the string is not mutable **rage** */
	tmp_copy = strdup(command);
	if (tmp_copy == NULL)
		return (-1);

	token = strtok(tmp_copy, delimiter); /* split string */
	while (token != NULL)
	{
		count++; /* count the next word */
		token = strtok(NULL, delimiter); /* move to next token */
	}

	/* Freeing the duplicated string */
	free(tmp_copy);
	return (count);
}

/**
 * call_args_error - print the error message if get_args fails.
*/
void call_args_error(void)
{
	perror("./hsh : ");
	exit(EXIT_FAILURE);
}

/**
 * **get_args - gets the arguments in a command string
 * @command: Command string to get arguments from
 * @delimiter: Character by which the string will be split by
 *
 * Description: Function would normally be used to split the arguments
 * using the space character i.e. " ". But a situation might occur that
 * would require us to split the input string differently.
 * One must ensure that either a mutable string or strdup of a string
 * is passed and must be freed as needed.
 *
 * Return: An array of arguments in input command.
*/
char **get_args(char *command, char *delimiter)
{
	char **args;
	char *token;
	int ind = 0, arg_count = 0;

	/**
	 * Finding out how many words we are allocating memory for.
	 * If the input is NULL, the count_args() function will
	 * return -1 and we call an error.
	*/
	arg_count = count_args(command, delimiter);
	if (arg_count == -1)
		call_args_error();

	/* Allocating the calculated memory for words */
	args = malloc((arg_count + 1) * sizeof(char *));
	/* if malloc fails */
	if (args == NULL)
		call_args_error();

	token = strtok(command, delimiter); /* split the string */
	for (ind = 0; ind < arg_count; ind++)
	{
		args[ind] = token; /* collect the word */
		token = strtok(NULL, delimiter);
	}

	/**
	 * NOTE: Dont forget to free the memory allocated of args if it is used
	 * to prevent memory leaks and valgrind errors.
	 *
	 * Another thing to consider is that this requires a mutable string input
	 * to work. That means you can only pass a string of type char string[] or
	 * the strdup of the string which must be freed later.
	 * 
	 * C IS JUST MESSED UP.
	*/
	args[arg_count] = NULL; /* making last index NULL to close the array */
	return (args);
}
