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

/* String functions */
char *trim_spaces(char *str);
int parse_args(char *line, char **args);

/* Path functions */
char *find_in_path(char *cmd);

/* Builtin functions */
int handle_exit(char **args, char *line, char *copy);
int handle_env(void);
int is_builtin(char **args, char *line, char *copy);

/* Execute functions */
void exec_cmd(char **args, char *line, char *copy, char *shell_name, int cmd_count);

#endif
