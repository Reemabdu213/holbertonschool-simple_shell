#include "main.h"

/**
 * main - Simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL, *copy, *trimmed, *args[64];
	size_t size = 0;
	ssize_t nread;
	int cmd_count = 0;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		nread = getline(&line, &size, stdin);

		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		cmd_count++;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		trimmed = trim_spaces(line);

		if (trimmed[0] == '\0')
			continue;

		copy = strdup(trimmed);
		if (!copy || parse_args(copy, args) == 0)
		{
			free(copy);
			continue;
		}

		exec_cmd(args, line, copy, argv[0], cmd_count);
		free(copy);
	}

	free(line);
	return (0);
}
