#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * *get_command - gets the user input using getline()
 *
 * Return: String containing input command.
*/
char *get_command()
{
	char *command = NULL;
	size_t command_buf_size = 0;
	ssize_t command_strlen;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 3); /* prompt the user */

	/* get the user command with the number of chars read returned */
	command_strlen = getline(&command, &command_buf_size, stdin);
	if (command_strlen == -1)
	{
		free(command);
		perror("./hsh: ");
		exit(EXIT_FAILURE);
	}

	if (command == NULL) /* Checking end of file condition */
	{
		free(command);
		exit(EXIT_SUCCESS);
	}

	if (command[0] == '\n')
	{
		free(command);
		return ("");
	}
	/**
	 * NOTE: the string that is used to collect the command must be freed
	 * using the free function. It is very important to avoid valgrind errors.
	*/
	return (command);
}
