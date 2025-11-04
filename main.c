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
 * main - Simple shell 0.1
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;
    char *args[2];
    char *trimmed;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        read = getline(&line, &len, stdin);
        
        if (read == -1)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        trimmed = trim_spaces(line);

        if (trimmed[0] == '\0')
            continue;

        pid = fork();
        
        if (pid == -1)
        {
            perror("Error");
            continue;
        }
        
        if (pid == 0)
        {
            args[0] = trimmed;
            args[1] = NULL;
            
            if (execve(trimmed, args, environ) == -1)
            {
                perror(trimmed);
                free(line);
                exit(127);
            }
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (0);
}
