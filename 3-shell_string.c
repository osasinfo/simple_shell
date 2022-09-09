#include "shell.h"

/**
 * _strlen - function that gets length of a string
 * @str: params string to get the length of
 * Return: the length
 */

int _strlen(char *str)
{
	int i = 0;

	while (str[i])
	{
		i++;
	}
	return (i);
}


/**
 * _strcmp - function that gets length of a string
 * @str1: params string to compare
 * @str2: params string to compare
 * Return: 0 if passed or -1 if failed
 */
int _strcmp(char *str1, char *str2)
{
	int len1 = _strlen(str1);

	int len2 = _strlen(str2);

	int i;

	if (len1 != len2)
	{
		return (-1);
	}
	while (str1[i])
	{
		if (str1[i] != str2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
