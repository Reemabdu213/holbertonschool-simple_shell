#include "main.h"

/**
 * exec_cmd - Execute command with arguments
 * @args: Array of arguments
 * @line: Original line
 * @copy: Copy of line
 * @shell_name: Name of shell for errors
 * @cmd_count: Command counter for error messages
 */
void exec_cmd(char **args, char *line, char *copy, char *shell_name, int cmd_count)
{
	pid_t pid;
	char *cmd_path;
	int status;

	if (is_builtin(args, line, copy))
		return;

	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", shell_name, cmd_count, args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		if (cmd_path != args[0])
			free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(args[0]);
			if (cmd_path != args[0])
				free(cmd_path);
			free(line);
			free(copy);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		if (cmd_path != args[0])
			free(cmd_path);
	}
}
