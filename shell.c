#include "main.h"

/**
 * process_line - Process a single command line
 * @line: Command line
 * @info: Shell info structure
 * Return: Exit status
 */
int process_line(char *line, t_shell *info)
{
	char *copy, *trimmed, *args[64];
	int status = 0;

	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	trimmed = trim_spaces(line);
	if (trimmed[0] == '\0')
		return (0);
	copy = strdup(trimmed);
	if (!copy || parse_args(copy, args) == 0)
	{
		free(copy);
		return (0);
	}
	status = exec_cmd(args, line, copy, info);
	free(copy);
	return (status);
}

/**
 * main - Simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	t_shell info;
	(void)argc;

	info.name = argv[0];
	info.cmd_count = 0;
	info.last_status = 0;
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
		info.cmd_count++;
		info.last_status = process_line(line, &info);
	}
	free(line);
	return (info.last_status);
}
