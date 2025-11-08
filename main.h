#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct shell_info - Shell information
 * @name: Shell name
 * @cmd_count: Command counter
 * @last_status: Last command exit status
 */
typedef struct shell_info
{
	char *name;
	int cmd_count;
	int last_status;
} t_shell;

char *trim_spaces(char *str);
int parse_args(char *line, char **args);
char *_getenv(char *name);
char *find_in_path(char *cmd);
int handle_exit(char **args, char *line, char *copy, int last_status);
int handle_env(void);
int is_builtin(char **args, char *line, char *copy, int last_status);
int exec_cmd(char **args, char *line, char *copy, t_shell *info);
int process_line(char *line, t_shell *info);

#endif
