#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

char *trim_spaces(char *str);
int parse_args(char *line, char **args);
void exec_cmd(char **args, char *line, char *copy);

#endif
