#include "main.h"

/**
 * _getenv - Get environment variable value
 * @name: Variable name
 * Return: Value or NULL
 */
char *_getenv(char *name)
{
	int i = 0, j;
	int len = strlen(name);

	while (environ[i])
	{
		j = 0;
		while (j < len && environ[i][j] == name[j])
			j++;
		if (j == len && environ[i][j] == '=')
			return (&environ[i][j + 1]);
		i++;
	}
	return (NULL);
}

/**
 * check_direct_path - Check if command path is valid
 * @cmd: Command to check
 * Return: Command if valid, NULL otherwise
 */
char *check_direct_path(char *cmd)
{
	if (strchr(cmd, '/'))
		return (access(cmd, X_OK) == 0 ? cmd : NULL);
	return (NULL);
}

/**
 * build_full_path - Build full path from directory and command
 * @dir: Directory path
 * @cmd: Command name
 * Return: Full path or NULL
 */
char *build_full_path(char *dir, char *cmd)
{
	char *full_path;

	full_path = malloc(strlen(dir) + strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	sprintf(full_path, "%s/%s", dir, cmd);
	return (full_path);
}

/**
 * search_in_path - Search command in PATH directories
 * @cmd: Command to find
 * @path_copy: Copy of PATH variable
 * Return: Full path or NULL
 */
char *search_in_path(char *cmd, char *path_copy)
{
	char *dir, *full_path;
	struct stat st;

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = build_full_path(dir, cmd);
		if (!full_path)
			return (NULL);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (full_path);
		free(full_path);
		dir = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * find_in_path - Find command in PATH
 * @cmd: Command to find
 * Return: Full path to command or NULL
 */
char *find_in_path(char *cmd)
{
	char *path, *path_copy, *result;

	result = check_direct_path(cmd);
	if (result)
		return (result);
	path = _getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);
	result = search_in_path(cmd, path_copy);
	free(path_copy);
	return (result);
}
