#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "shell.h"

/**
 * bin_exit - exits the program for the exit builtin
 *
 * Return: Nothing
 */
int bin_exit(void)
{
	exit(EXIT_SUCCESS); /* We are leaving regardless */
	return (0);
}

/**
 * bin_env - prints the enviromental variable for the env builtin
 *
 * Return: -1 if the function fails, 0 if nothing happens
 */
int bin_env(void)
{
	char *argv[] = {"/usr/bin/printenv", NULL};
	int status = execve("/usr/bin/printenv", argv, NULL);

	/* The plan is to call the printenv function */
	if (status == -1)
	{
		perror("./hsh: ");
		return (-1);
	}
	return (-1); /* if we reach here, the code clearly failed */
}

/**
 * get_builtin - gets the builtin function from the type
 * @cmd: Builtin/command name
 *
 * Return: function pointer for specific builtin command
 */
int (*get_builtin(char *cmd))(void)
{
	int i;
	builtin bins[] = {
		{"exit", bin_exit()},
		{"env", bin_env()},
		{NULL, NULL}
	};

	/**
	 * Checks through each builtin to compare name and returns
	 * one that matches
	 */
	for (i = 0; bins[i].name != NULL, i++)
	{
		if (_strcmp(input_args[0], bins[i].name) == 0)
			return (bins[i].func);
	}

	return (NULL);
}
