#include "main.h"

/**
 * print_error - Print error message
 * @shell_name: Name of shell
 * @cmd_count: Command counter
 * @cmd: Command that failed
 */
void print_error(char *shell_name, int cmd_count, char *cmd)
{
	fprintf(stderr, "%s: %d: %s: not found\n",
		shell_name, cmd_count, cmd);
}

/**
 * exec_child - Execute command in child process
 * @cmd_path: Full path to command
 * @args: Array of arguments
 * @line: Original line
 * @copy: Copy of line
 */
void exec_child(char *cmd_path, char **args, char *line, char *copy)
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

/**
 * exec_cmd - Execute command with arguments
 * @args: Array of arguments
 * @line: Original line
 * @copy: Copy of line
 * @info: Shell info structure
 * Return: Exit status of command
 */
int exec_cmd(char **args, char *line, char *copy, t_shell *info)
{
	pid_t pid;
	char *cmd_path;
	int status;

	if (is_builtin(args, line, copy, info->last_status))
		return (0);
	cmd_path = find_in_path(args[0]);
	if (!cmd_path)
	{
		print_error(info->name, info->cmd_count, args[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		if (cmd_path != args[0])
			free(cmd_path);
		return (1);
	}
	if (pid == 0)
		exec_child(cmd_path, args, line, copy);
	else
	{
		wait(&status);
		if (cmd_path != args[0])
			free(cmd_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
