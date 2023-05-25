#include "shell.h"
#include "string.h"

/**
 * _strlen - return length of string
 * @str: the string
 * Return: length of string
 */

int _strlen(const char *str)
{
	int len;

	if (!str)
		return (0);

	len = 0;
	while (*str)
	{
		str += 1;
		len += 1;
	}

	return (len);

}

