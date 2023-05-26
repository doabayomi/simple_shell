#include "shell.h"

/**
 * *get_input - collects input using getline
 *
 * Return: input string.
 */
char *get_input(void)
{
	char *input = NULL;
	size_t input_buf_size = 0;
	ssize_t input_len;

	input_len = getline(&input, &input_buf_size, stdin);
	/* Handling error in collecting input */
	if (input_len == -1) /* getline error */
	{
		perror("Could not getline");
		exit(EXIT_FAILURE);
	}

	if (input == NULL) /* end of file condition */
		exit(EXIT_SUCCESS);

	/* Don't forget to free the input when calling this function */
	return (input);
}
