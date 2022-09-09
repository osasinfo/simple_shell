#include "shell.h"

void ctrl_C(int signum)
{
	if (signum == SIGINT)
	{
		print("\n ($) ", STDIN_FILENO);
	}
}

/**
 * _getline - receives input from the user
 * Return: return the input
 */

char *_getline(void)
{
	int bufSize = READ_BUF, noread, position = 0;

	char *buffer = malloc(bufSize * sizeof(char));

	char c;

	if (buffer == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		noread = read(STDIN_FILENO, &c, 1);
		if (c == EOF || !noread)
		{
			if (isatty(STDIN_FILENO) == 1)
			{
				print("\n", STDIN_FILENO);
				return (NULL);
			}
		}
		else if (c == '\n' || !noread)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;
		if (position >= bufSize)
		{
			bufSize += READ_BUF;
			buffer = _realloc(buffer, READ_BUF, bufSize);
			if (!buffer)
				perror("Fail to allocate space in the memory");
				exit(EXIT_FAILURE);
		}
	}
}

int is_delimeter(const char *delimeters, char c);

/**
 * tokenize - function that split strings
 * @str: string to split
 * @delim: character to split the string with
 * Return: pointer to new string or NULL
 */

char **tokenize(char *str, const char *delim)
{
	int k = 0, j = 0, i = 0, size = 0, lens[1200];

	char **arr;

	if (str == NULL || !(*str))
	{
		return (NULL);
	}
	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
		{
			continue;
		}
		j = i;
		while (!is_delimeter(delim, str[i]) && str[i])
		{
			i++;
		}
		if (i > j)
		{
			lens[size++] = i - j;
		}
		if (!str[i])
		{
			break;
		}
	}
	if (!size)
		return (NULL);
	arr = malloc((size + 1) * sizeof(char *));
	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
		{
			continue;
		}
		arr[k] = malloc((lens[k] + 1) * sizeof(char));
		j = 0;
		while (!is_delimeter(delim, str[i]) && str[i])
		{
			arr[k][j++] = str[i++];
		}
		arr[k++][j] = '\0';
		if (!str[i])
		{
			break;
		}
	}
	arr[size] = NULL;
	return (arr);
}

/**
 * is_delimeter - check if a character is delimeter
 * @delimeters: pointer to delimeters
 * @c: checking character
 * Return: 1 if passed or 0 if failed
 */

int is_delimeter(const char *delimeters, char c)

{
	int i = 0;

	if (!delimeters)
	{
		return (0);
	}
	while (delimeters[i])
	{
		if (delimeters[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
/**
 * shell_execute - function that executes the shell commands
 * @command: the input command
 * @cmd_type: the type of command
 * Return: 0 is passed;
 */

void shell_execute(char **command, int cmd_type)
{
	int start;

	pid_t PID;

	if (cmd_type == EXTERNAL_CMD || cmd_type == PATH_CMD)
	{
		PID = fork();
		if (PID == 0)
			execute(command, cmd_type);
		if (PID < 0)
			perror("failed to call fork");
			exit(1);
		else
			wait(&start);
	}
	else
		execute(command, cmd_type);
}

/**
 * check_command - function that check the input command
 * @command: input command
 * Return: 0 if fail
 */

int check_command(char *command)
{
	int i = 0;

	char *int_cmd[] = {"exit", "cd", "env", NULL};

	while (command[i])
	{
		if (command[i] == '/')
		{
			return (EXTERNAL_CMD);
		}
		i++;
	}
	i = 0;
	while (int_cmd[i] != NULL)
	{
		if (_strcmp(command, int_cmd[i]) == 0)
		{
			return (INTERNAL_CMD);
		}
		i++;
	}
	return (INVALID_CMD);
}

/**
 * execute - function that execute a command
 * @cmd_type: command type
 * @commands: input commands
 * Return: No return
 */

void execute(char **commands, int cmd_type)
{
	void (*func)(char **command);

	switch (cmd_type)
	{
		case EXTERNAL_CMD:
			{
				if (execve(commands[0], commands, NULL) == -1)
				{
					perror(_getenv("PWD"));
					exit(2);
				}
				break;
			}
		case INTERNAL_CMD:
			{
				func = get_func(commands[0]);
				func(commands);
				break;
			}
		case PATH_CMD:
			{
				break;
			}
		case INVALID_CMD:
			{
				break;
			}
	}
}
