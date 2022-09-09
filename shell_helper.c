#include "shell.h"

/**
 * print - print a command
 * @var: input variables
 * @fd: number of inputs
 * Return: Value
 */

int print(char *var, int fd)
{
	return (write(fd, var, _strlen(var)));
}


/**
 * get_func - get a function
 * @command: The input command
 * No desc
 * Return: NULL
 */

void (*get_func(char *command))(char **)
{
	int i;

	map_func map[] = {
		{"env", env},
		{"cd", ch_dir},
		{"exit", quit}
	};
	for (i = 0; i < 3; i++)
	{
		if (_strcmp(command, map[i].cmd_name)
				== 0)
			return (map[i].func);
	}
	return (NULL);
}
