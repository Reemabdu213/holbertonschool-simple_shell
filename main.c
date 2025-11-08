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
