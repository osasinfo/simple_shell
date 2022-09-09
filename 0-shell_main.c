#include "shell.h"

/**
 * main - entry point to the shell programm
 * @argv: argument vector
 * @argc: argument count
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char *line;

	char **args;

	int cmd;

	(void) argv;

	signal(SIGINT, ctrl_C);

	while (1)
	{
		print(" ($) ", STDOUT_FILENO);
		line = _getline();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				break;
		}
		args = tokenize(line, DELIM);
		cmd = check_command(args[0]);
		shell_execute(args, cmd);
	}
	return (1);
}
