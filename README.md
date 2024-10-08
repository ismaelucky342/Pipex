# Pipex
The goal of the project is to replicate some of the way the Unix shell's pipe operator (|) works.

The program takes commands and connects them using pipes, so that the output of one command is the input of the next. The basic steps include:
- Using pipes: The pipe() function is used to create a pipe between two processes.
- Fork and exec: Child processes are created using fork() and commands are executed using execve().
- Input and output redirection: Dup2() is used to redirect standard input and output to the appropriate ends of the pipe.
- File handling: Files are opened for reading and writing, using functions such as open().
- Errors: Errors are handled appropriately to avoid memory or resource leaks.

The creation of this project was born from the need to understand many of the bases and functions necessary for the creation of the minishell.
