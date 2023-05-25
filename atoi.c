#include "shell.h"

/**
 * _atoi - convert string to integer
 * @s: the string
 * Return: integer
 */

int _atoi(char *str)
{
	unsigned int n = 0, sign = 1, started = 0;

	while (*str)
	{
		if (started && !(*str >= '0' && *str <= '9'))
			break;
		if (*str == '-')
			sign *= -1;
		if ((*str >= '0' && *str <= '9'))
		{
			started = 1;
			n =  n * 10 + (int)*str - 48;
		}
		str++;
	}
	return (sign * n);
}

