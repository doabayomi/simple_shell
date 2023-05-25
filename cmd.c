#include "shell.h"

/**
 * _chdir - change current directory
 * @path: new path
 * Return: 0 on sucess and 1 on failure
 */

int _chdir(char *path)
{
	int stat, exitstat = 0;
	char *currentdir = _getenv("PWD"), *buf = NULL, *cdir, *msg;
	char *tail;
	size_t size = 0;

	if (!path || !_strcmp(path, "~"))
		stat = chdir(_getenv("HOME"));
	else if (!_strcmp(path, "-"))
		stat = chdir(_getenv("OLDPWD"));
	else
		stat = chdir(path);
	if (stat < 0)
	{
		errno = -3;
		msg = _malloc(_strlen("No such file or directory exist") + _strlen(path) + 4);
		_strcpy(msg, "No such file or directory exist ");
		tail = _malloc(_strlen("cd: ") + _strlen(path) + 4);
		_strcpy(tail, "cd: "), _strcat(tail, path);
		print_error(tail, NULL, msg);
		free(msg), free(tail);
		exitstat = 1;
	}

	_setenv("OLDPWD", currentdir, 1);
	cdir = getcwd(buf, size);
	_setenv("PWD", cdir, 1);
	free(buf), free(cdir);
	return (exitstat);
}

