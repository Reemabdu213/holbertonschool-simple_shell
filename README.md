# Simple Shell

A simple UNIX command line interpreter written in C.

## Description

This project is a simple shell implementation that replicates the basic functionality of the **sh** shell.  
It displays a prompt, reads commands from the user, parses them, and executes them using system calls such as `fork`, `execve`, and `wait`.

## Installation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode
```bash
$ ./hsh
$ ls -l
$ pwd
$ exit
```

### Non-Interactive Mode
```bash
$ echo "ls" | ./hsh
$ echo "/bin/ls" | ./hsh
```

## File Structure

- `main.c` - Entry point of the shell  
- `path.c` - Handles PATH resolution and command search  
- `builtins.c` - Built-in commands (exit, env)  
- `execute.c` - Command execution logic  
- `shell.c` - Main shell loop and input handling  
- `main.h` - Header file containing function prototypes and macros

## Built-in Commands

### exit [status]
Exit the shell with an optional status.
```bash
$ exit
$ exit 98
```

### env
Print the current environment variables.
```bash
$ env
```

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Testing
```bash
echo "ls" | ./hsh
echo "/bin/pwd" | ./hsh
echo "env" | ./hsh
```

## Authors

- **Dalal Saleh Alshamrani** - 11969@holbertonstudents.com  
- **Reem Abdullah Al-Dosari** - 11972@holbertonstudents.com  

## License

This project is part of the ALX Software Engineering program.  
All rights reserved © 2025 ALX & contributors.
