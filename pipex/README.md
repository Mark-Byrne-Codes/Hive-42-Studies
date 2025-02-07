# Pipex

A 42 school project that recreates Unix pipes functionality. This program simulates the behavior of the shell pipe operator `|`, allowing command output redirection between processes.

## Overview

Pipex takes an input file, two commands, and an output file to create a pipeline where:
- The first command reads from the input file
- The second command receives output from the first command
- Final output is written to the output file

The program implements the following shell behavior:
```bash
< file1 cmd1 | cmd2 > file2
```
Using the format:
```bash
./pipex file1 cmd1 cmd2 file2
```

## Installation

Clone the repository and compile the program:
```bash
git clone <repository-url>
cd pipex
make
```

## Usage

Basic syntax:
```bash
./pipex <input_file> <cmd1> <cmd2> <output_file>
```

Example usage:
```bash
# Count number of lines in a file
./pipex input.txt "cat" "wc -l" output.txt

# Find specific words and replace them
./pipex input.txt "grep hello" "sed s/hello/hi/g" output.txt

# List files and count them
./pipex input.txt "ls -l" "wc -l" output.txt
```

## Error Handling

The program handles various error cases:
- Non-existent input files
- Permission denied errors
- Invalid commands
- Incorrect number of arguments

## Testing

Here are some test cases to verify functionality:

1. Basic operation:
```bash
echo "hello world" > input.txt
./pipex input.txt "grep hello" "wc -l" output.txt
```

2. Error handling:
```bash
# Non-existent input file
./pipex nonexistent "cat" "wc -l" output.txt

# Invalid command
./pipex input.txt "invalidcmd" "wc -l" output.txt
```

3. Complex commands:
```bash
# Using quotes in commands
./pipex input.txt "grep 'hello world'" "sed 's/hello/hi/g'" output.txt

# Environment variables
./pipex input.txt "env" "grep PATH" output.txt
```

## Project Structure

Key components:
- `pipex.h`: Header file containing structure definitions and function prototypes
- `pipex.c`: Main program logic and process management
- `utils.c`: Utility functions for file and command handling
- `path.c`: Path resolution and environment variable handling

## Resources

For more information on the concepts used in this project:
- `pipe()`: [Linux manual](https://man7.org/linux/man-pages/man2/pipe.2.html)
- `fork()`: [Linux manual](https://man7.org/linux/man-pages/man2/fork.2.html)
- `execve()`: [Linux manual](https://man7.org/linux/man-pages/man2/execve.2.html)

## Author

Mark Byrne - Mbyrne

## Acknowledgments

This project is part of the 42 school curriculum.