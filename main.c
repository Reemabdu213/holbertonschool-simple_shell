#include "main.h"

/**
 * trim_spaces - Remove leading and trailing spaces
 * @str: String to trim
 * Return: Pointer to trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '\0')
		return (str);
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = '\0';
	return (str);
}

/**
 * parse_args - Parse command line into arguments
 * @line: Command line string
 * @args: Array to store arguments
 * Return: Number of arguments
 */
int parse_args(char *line, char **args)
{
	int i = 0;
	char *token = strtok(line, " \t\n");

	while (token && i < 63)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (i);
}

/**
 * exec_cmd - Execute command with arguments
 * @args: Array of arguments
 * @line: Original line
 * @copy: Copy of line
 */
void exec_cmd(char **args, char *line, char *copy)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error");
		return;
	}
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			free(line);
			free(copy);
			exit(127);
		}
	}
	else
		wait(NULL);
}

/**
 * main - Simple shell
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL, *copy, *trimmed, *args[64];
	size_t size = 0;
	ssize_t nread;

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
		exec_cmd(args, line, copy);
		free(copy);
	}
	free(line);
	return (0);
}
