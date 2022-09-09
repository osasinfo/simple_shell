#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int index, k;
	char *str = dest;

	index = 0;
	while (src[index] != '\0' && index < n - 1)
	{
		dest[index] = src[index];
		index++;
	}
	if (index < n)
	{
		k = index;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (str);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int index, k;
	char *str = dest;

	index = 0;
	k = 0;
	while (dest[index] != '\0')
		index++;
	while (src[k] != '\0' && k < n)
	{
		dest[index] = src[k];
		index++;
		k++;
	}
	if (k < n)
		dest[index] = '\0';
	return (str);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
