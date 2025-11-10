 #include "main.h"

/**
 * handle_exit - Handle exit builtin
 * @args: Array of arguments
 * @line: Original line
 * @copy: Copy of line
 * @last_status: Last command exit status
 * Return: 1 to exit, 0 to continue
 */
int handle_exit(char **args, char *line, char *copy, int last_status)
{
	int status = last_status;

	if (args[1])
		status = atoi(args[1]);
	free(line);
	free(copy);
	exit(status);
}

/**
 * handle_env - Handle env builtin
 * Return: Always 0
 */
int handle_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

/**
 * is_builtin - Check if command is builtin
 * @args: Array of arguments
 * @line: Original line
 * @copy: Copy of line
 * @last_status: Last command exit status
 * Return: 1 if builtin executed, 0 otherwise
 */
int is_builtin(char **args, char *line, char *copy, int last_status)
{
	if (strcmp(args[0], "exit") == 0)
	{
		handle_exit(args, line, copy, last_status);
		return (1);
	}
	if (strcmp(args[0], "env") == 0)
	{
		handle_env();
		return (1);
	}
	return (0);
}
