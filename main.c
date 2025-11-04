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
 * parse_command - Parse command line into arguments
 * @line: Command line string
 * @args: Array to store arguments
 * Return: Number of arguments
 */
int parse_command(char *line, char **args)
{
	int i = 0;
	char *token;

	token = strtok(line, " \t\n");
	while (token != NULL && i < 63)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	return (i);
}

/**
 * execute_command - Fork and execute command
 * @args: Array of arguments
 * @line: Original line for memory cleanup
 * @line_copy: Copy of line for memory cleanup
 */
void execute_command(char **args, char *line, char *line_copy)
{
	pid_t pid;
	int status;

	pid = fork();

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
			free(line_copy);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Simple shell 0.1
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL, *line_copy = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[64];
	char *trimmed;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		trimmed = trim_spaces(line);

		if (trimmed[0] == '\0')
			continue;

		line_copy = strdup(trimmed);
		if (line_copy == NULL || parse_command(line_copy, args) == 0)
		{
			free(line_copy);
			continue;
		}

		execute_command(args, line, line_copy);
		free(line_copy);
	}

	free(line);
	return (0);
}
