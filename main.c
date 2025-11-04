#include "main.h"

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

        if (line[0] == '\0')
            continue;

        pid = fork();
        
        if (pid == -1)
        {
            perror("Error");
            continue;
        }
        
        if (pid == 0)
        {
            args[0] = line;
            args[1] = NULL;
            
            if (execve(line, args, environ) == -1)
            {
                perror(line);
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
