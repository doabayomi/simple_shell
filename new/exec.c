#include "builtins.h"

/**
 * __exec - replace the running shell with a new program
 * @info: arguments passed
 * Return: int
 */
int __exec(info_t *info)
{
	char *execu, **args = info->tokens + 1, **envir = NULL;

	if (!*args)
		return ((info->status = EXIT_SUCCESS));

	info->tokens = args;
	args = arrdup(args);

	if (_strchr(*args, '/') == -1)
	{
		free_list(&info->path);
		info->path = str_to_list(get_dict_val(info->env, "PATH"), ':');
		execu = search_path(info, info->path);
	}
	else
	{
		execu = _strdup(*args);
	}
	info->tokens -= 1;

	if (access(execu, X_OK) == 0)
	{
		envir = dict_to_envir(info->env);

		free_info(info);
		execve(execu, args, envir);
		perrorl_default(*info->argv, info->lineno, "Not found",
				*info->tokens, *args, NULL);
		free(execu);
		free_tokens(&args);
		free_tokens(&envir);
		exit(127);
	}
	perrorl_default(*info->argv, info->lineno, "Permission denied",
			*info->tokens, *args, NULL);
	free(execu);
	free_tokens(&args);
	free_info(info);
	exit(126);
}

