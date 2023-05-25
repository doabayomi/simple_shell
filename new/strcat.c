#include "stdio.h"
#include "string.h"


/**
 * _strcat - concatinate 2 strings
 * @dest: string destination
 * @src: source string
 *
 * Return: concatinated string
 */

char *_strcat(char *dest, char *src)
{
	char *t = dest;

	while (*t)
		t++;

	while (*src)
		*t++ = *src++;

	*p = '\0';

	return (dest);
}

