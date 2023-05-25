#include "shell.h"
#define l(x) _strlen((x))
#define cch const char

/**
 * _putenv - write to env variables
 * @es: env var value arg pair
 * Return: 0 on success and -1 on faliure
 */

int _putenv(char *es)
{
	char **_environ = environ, **newenviron, **_newenviron;
	int l = 0;

	while (*_environ)
		l++, _environ++;

	newenviron = _malloc(sizeof(char *) * (l + 4));
	_newenviron = newenviron;
	_environ =  environ;
	while (l)
	{
		*_newenviron = _malloc(sizeof(char) * _strlen(*_environ) + 4);
		_strcpy(*_newenviron, *_environ);
		_newenviron++, _environ++, l--;
	}
	*_newenviron = _malloc(sizeof(char) * _strlen(es) + 4);
	_strcpy(*_newenviron, es);
	free(es);
	_newenviron++;
	*_newenviron = NULL;
	free_pp(environ);
	environ = newenviron;
	return (0);
}

/**
 * _setenv - set env variables
 * @name: variable name
 * @value: value
 * @overwrite: overwrite status
 *
 * Return: 0 on success and -1 on faliure
 */

int _setenv(cch *name, cch *value, __attribute__((unused))int overwrite)
{
	char *evs, **evp, *var;
	int k = 0;

	if (name == NULL || name[0] == '\0' || value == NULL)
		return (-1);

	if (environ)
	{
		evp = _arrdup(environ);
		while (evp[k])
		{

			var = _strtok(evp[k], "=", 0);
			if (!_strcmp(var, (char *)name))
			{
				free(environ[k]);
				environ[k] = _malloc(_strlen(name) + _strlen(value) + 4);
				_strcpy(environ[k], (char *)name);
				_strcat(environ[k], "=");
				_strcat(environ[k], (char *)value);
				free_pp(evp);
				return (0);
			}
			k++;
		}
		free_pp(evp);
	}
	evs = _malloc(_strlen(name) + _strlen(value) + 2);
	if (evs == NULL)
		return (-1);
	_strcpy(evs, (char *)name), _strcat(evs, "="), _strcat(evs, (char *)value);
	return ((_putenv(evs) != 0) ? -1 : 0);
	free(evs);
}

/**
 * _unsetenv - delete env variables
 * @name: name of varaible
 * Return: 0 on success and -1 on faliure
 */

int _unsetenv(const char *name)
{
	char **evp, **sp, *var, *value;

	if (name == NULL || name[0] == '\0')
		return (-1);
	evp = _arrdup(environ);
	free_pp(environ);
	environ = _malloc(sizeof(char *));

	for (sp = evp; *sp != NULL; )
	{

		var = _strtok(*sp, "=", 0);
		if (_strcmp(var, (char *)name))
		{
			value = _strtok(NULL, "=", 0);
			_setenv(var, value, 1);
		}
		sp++;
	}
	free_pp(evp);
	return (0);
}

/**
 * _printenv - print env variables
 */

void _printenv(void)
{
	char **_env = environ;

	if (!_env)
		return;
	_write(-1, NULL, 0);
	while (*_env)
	{
		write(1, *_env, _strlen(*_env));
		write(1, "\n", 1);
		_env++;
	}
	write(1, NULL, 0);
}



/**
 * _getenv - get env variables
 * @name: name of variable
 * Return: pointer to env variables
 */

char *_getenv(const char *name)
{
	int len, k;
	const char *nip;
	char **p, *cip;

	if (name == NULL || environ == NULL)
		return (NULL);
	for (nip = name; *nip && *nip != '='; ++nip)
		;
	len = nip - name;
	for (p = environ; (cip = *p) != NULL; ++p)
	{
		for (nip = name, k = len; k && *cip; k--)
			if (*cip++ != *nip++)
				break;
		if (k == 0 && *cip++ == '=')
			return (cip);
	}
	return (NULL);
}

