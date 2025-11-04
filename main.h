#ifndef MAIN_H
#define MAIN_H

/* Standard headers used by the implementation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

/* Expose environment */
extern char **environ;

/* Max args for parser */
#define MAX_ARGS 64

/* Function prototypes (match signatures used in main.c) */
char *trim_spaces(char *str);
int parse_args(char *line, char **args);
/* exec_cmd uses: args (token array), line (original getline buffer), copy (strdup buffer) */
void exec_cmd(char **args, char *line, char *copy);

#endif /* MAIN_H */
