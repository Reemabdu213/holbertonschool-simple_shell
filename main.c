#include "main.h"

/**
 * main - simple shell loop
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &size, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}

		/* remove newline at the end */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (fork() == 0)
		{
			execlp(line, line, NULL);
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}

	return (0);
}
