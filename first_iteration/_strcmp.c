#include <stdio.h>
#include <stdlib.h>

/**
 * _strcmp - Simple strcmp implementation
 * @first: First string to compare
 * @second: Second string to compare
 *
 * Return: 1 if both strings match, -1 otherwise.
*/
int _strcmp(char *first, char *second)
{
	int ind = 0;

	while (first[ind] == second[ind])
	{
		if (first[ind] == '\0')
			return (0);
		ind++;
	}

	return (first[ind] - second[ind]);
}
