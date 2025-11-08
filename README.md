# Simple Shell

A simple UNIX command line interpreter written in C.

## Description

This project is a simple shell implementation that replicates basic functionality of the sh shell. It displays a prompt, reads commands from the user, finds and executes them, and displays the prompt again.

## Features

- Display a prompt and wait for user input
- Execute commands with arguments
- Search for executables in the PATH
- Handle command lines with arguments
- Implement built-in commands:
  - `exit [status]` - Exit the shell
  - `env` - Print current environment
- Handle errors appropriately
- Handle the "end of file" condition (Ctrl+D)
- Handle Ctrl+C (does not exit the shell)

## Installation

Clone the repository and compile:
```bash
git clone https://github.com/yourusername/simple_shell.git
cd simple_shell
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode
```bash
$ ./hsh
$ ls -l
$ pwd
$ echo "Hello World"
$ exit
```

### Non-Interactive Mode
```bash
$ echo "ls" | ./hsh
$ echo "/bin/ls" | ./hsh
$ cat test_file | ./hsh
```

## Examples
```bash
$ ./hsh
$ ls
AUTHORS  builtins.c  execute.c  hsh  main.c  main.h  man_1_simple_shell  path.c  README.md  shell.c
$ pwd
/home/user/simple_shell
$ /bin/echo "Hello World"
Hello World
$ env
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/user
USER=user
...
$ exit
$
```

## File Structure

- `main.c` - String manipulation functions (trim_spaces, parse_args)
- `path.c` - PATH handling and command search functions
- `builtins.c` - Built-in commands implementation (exit, env)
- `execute.c` - Command execution functions
- `shell.c` - Main shell loop
- `main.h` - Header file with function prototypes and structures
- `AUTHORS` - List of contributors
- `README.md` - This file
- `man_1_simple_shell` - Manual page

## Built-in Commands

### exit [status]
Exit the shell with an optional exit status.

**Usage:**
```bash
$ exit
$ exit 98
```

If no status is provided, the exit status of the last executed command is used.

### env
Print the current environment variables.

**Usage:**
```bash
$ env
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/user
USER=user
SHELL=/bin/bash
...
```

## Requirements

### General
- Allowed editors: vi, vim, emacs
- All files will be compiled on Ubuntu 20.04 LTS using gcc
- All files should end with a new line
- Code should use the Betty style
- Shell should not have any memory leaks
- No more than 5 functions per file
- All header files should be include guarded
- Use system calls only when you need to

### Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Allowed Functions and System Calls
- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `getpid` (man 2 getpid)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (__xstat) (man 2 stat)
- `lstat` (__lxstat) (man 2 lstat)
- `fstat` (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)

## Testing

### Check Betty Style
```bash
betty-style *.c *.h
betty-doc *.c *.h
```

### Test Commands
```bash
# Test basic commands
echo "ls" | ./hsh
echo "pwd" | ./hsh

# Test with full path
echo "/bin/ls" | ./hsh

# Test with arguments
echo "ls -la" | ./hsh

# Test built-ins
echo "env" | ./hsh
echo "exit" | ./hsh

# Test error handling
echo "invalid_command" | ./hsh

# Test interactive mode
./hsh
```

### Memory Leak Check
```bash
valgrind --leak-check=full ./hsh
```

## Project Tasks

### Task 0: Betty would be proud
Write a beautiful code that passes the Betty checks.

### Task 1: Simple shell 0.1
Write a UNIX command interpreter that:
- Displays a prompt and wait for the user to type a command
- Handles simple command lines (no semicolons, pipes, redirections, etc.)
- Handles errors and "end of file" condition (Ctrl+D)

### Task 2: Simple shell 0.2
Handle command lines with arguments.

### Task 3: Simple shell 0.3
Handle the PATH.
Fork only when the command to execute is found.

### Task 4: Simple shell 0.4
Implement the exit built-in that exits the shell.
Usage: `exit [status]`

### Task 5: Simple shell 1.0
Implement the env built-in that prints the current environment.

### Task 6: Write your own getenv function
Implement `_getenv` without using the standard library function `getenv`.

### Task 7: Write your own strtok function
Implement `_strtok` if needed.

## Known Limitations

- Does not handle pipes (`|`)
- Does not handle redirections (`>`, `<`, `>>`)
- Does not handle command separators (`;`, `&&`, `||`)
- Does not handle special characters (`*`, `?`, `~`, etc.)
- Does not handle variables (`$`, `$?`, `$$`)
- Does not handle comments (`#`)
- Does not handle command history
- Does not handle tab completion

## Authors

- **Dalal Saleh Alshamrani** - [11969@holbertonstudents.com](mailto:11969@holbertonstudents.com)
- **Reem Abdullah Aldosri** - [11972@holbertonstudents.com](mailto:11972@holbertonstudents.com)

See [AUTHORS](AUTHORS) file for complete list of contributors.

## License

This project is part of the ALX Software Engineering program.

## Acknowledgments

- ALX Africa
- Holberton School
- All peer reviewers and mentors

## Resources

- [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
- [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)
- [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)
- [Everything you need to know to start coding your own shell concept page](https://intranet.alxswe.com/concepts/64)

## Contact

For questions or feedback, please contact the authors via their email addresses listed above.

---

**Project Start Date:** November 2024  
**Project End Date:** November 2024  
**Version:** 1.0
