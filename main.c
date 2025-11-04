/* main.c */
#include "main.h"

/* helper: search command in PATH, return malloc'ed path or NULL */
static char *find_in_path(char *cmd)
{
	char *path_env, *dup, *token;
	size_t len;
	char *full;

	if (!cmd)
		return (NULL);

	/* if command contains a slash, treat it as a path */
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	dup = strdup(path_env);
	if (!dup)
		return (NULL);

	token = strtok(dup, ":");
	while (token)
	{
		len = strlen(token) + 1 + strlen(cmd) + 1;
		full = malloc(len);
		if (!full)
		{
			free(dup);
			return (NULL);
		}
		snprintf(full, len, "%s/%s", token, cmd);
		if (access(full, X_OK) == 0)
		{
			free(dup);
			return (full);
		}
		free(full);
		token = strtok(NULL, ":");
	}
	free(dup);
	return (NULL);
}

/**
 * trim_spaces - Remove leading and trailing spaces
 * @str: String to trim
 * Return: Pointer to trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	if (!str)
		return (str);
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
 * @line: Command line string (modified by strtok)
 * @args: Array to store arguments
 * Return: Number of arguments
 */
int parse_args(char *line, char **args)
{
	int i = 0;
	char *token;

	if (!line || !args)
		return (0);

	token = strtok(line, " \t\n");
	while (token && i < (MAX_ARGS - 1))
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
 * @line: Original line pointer (so child can free before exiting)
 * @copy: Copy of line (token buffer) (so child can free before exiting)
 *
 * Note: exec_cmd will search PATH for the executable. It will fork and execve.
 * The child frees line and copy before exiting on error.
 */
void exec_cmd(char **args, char *line, char *copy)
{
	pid_t pid;
	int status;
	char *resolved = NULL;

	if (!args || !args[0])
		return;

	/* resolve path if necessary */
	resolved = find_in_path(args[0]);
	if (resolved)
		args[0] = resolved;
	else
	{
		/* if user provided a path (contains '/'), we'll try it as-is;
		   otherwise print not found and return */
		if (!strchr(args[0], '/'))
