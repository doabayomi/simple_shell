#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "shell.h"

/**
 * *get_env_var - get the variable name/value of a environment variable
 * @env_var: The specific environment variable string in question
 *
 * Return: Name of the environment variable if value is 0
 * Value of environment variable if value is greater than 1
 * NULL if something fails
*/
char *get_env_var(char *env_var, int value) {
	char *var = strdup(env_var);
	char *var_name;
	char **env = get_args(var, "=");

	if (env == NULL) {
		printf("Failed to extract variable name from the environment variable.\n");
		free(var);
		return NULL;
	}

	if (value == 0)
		var_name = strdup(env[0]);
	else
		var_name = strdup(env[1]);

	free(env);
	free(var);
	return var_name;
}
