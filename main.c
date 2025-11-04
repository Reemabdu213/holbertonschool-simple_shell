#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

/**
 * read_line - read a line from stdin using getline
 * Return: pointer to malloc'd string (caller must free) or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1) /* EOF or error */
	{
		free(line);
		return (NULL);
	}
	/* remove trailing newline */
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	return (line);
}

/**
 * parse_line - split a line into array of args
 * @line: input line (will be tokenized)
 *
 * Return: NULL-terminated array of strings (caller must free entries
 * and the array) or NULL on allocation failure
 */
char **parse_line(char *line)
{
	int bufsize = 64, pos = 0;
	char **tokens = NULL;
	char *token, *saveptr;

	if (!line)
		return (NULL);

	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
		return (NULL);

	token = strtok_r(line, " \t\r\n", &saveptr);
	while (token)
	{
		tokens[pos] = strdup(token);
		if (!tokens[pos])
		{
			/* free allocated tokens so far */
			for (int i = 0; i < pos; i++)
				free(tokens[i]);
			free(tokens);
			return (NULL);
		}
		pos++;
		if (pos >= bufsize)
		{
			bufsize *= 2;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
				return (NULL);
		}
		token = strtok_r(NULL, " \t\r\n", &saveptr);
	}
	tokens[pos] = NULL;
	return (tokens);
}

/**
 * free_args - free array returned by parse_line
 * @args: NULL-terminated array to free
 */
void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * execute_command - execute program given args using fork + execve
 * @args: NULL-terminated arguments array
 *
 * Notes: This function expects args[0] to be the path to the executable
 * (no PATH search is performed here).
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;

	if (!args || !args[0])
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0) /* child */
	{
		execve(args[0], args, environ);
		/* if execve returns, an error happened */
		dprintf(STDERR_FILENO, "hsh: %s: %s\n", args[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
	else /* parent */
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
	}
}

/**
 * main - simple shell loop (Task 2: handle arguments)
 * Return: 0 on normal exit
 */
int main(void)
{
	char *line;
	char **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		line = read_line();
		if (line == NULL) /* EOF */
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		args = parse_line(line);
		free(line); /* parse_line duplicated tokens, safe to free line */

		if (!args)
			continue;

		execute_command(args);
		free_args(args);
	}
	return (0);
}
