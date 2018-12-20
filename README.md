# TinyShell
Implemented a command line interpreter program (shell) that operates in the following way: when we type in a command, the shell creates a new child process that executes the command; after it finishes, it prompts for the next user input. 

In this project, I implemented two built-in commands, "exit" and "history". For all the other commands of the shell program, the program handles them by using the system()in C++, which is used to invoke a command execution from a C/C++ program.

About the history command, it displays an ordered list of all input commands that a shell received in a session. In this project, by default, the history command is only required to display 5 most recent commands (latest command shows first; if less than 5 commands has been executed, all are shown). The shell records all commands it receives from the command line. Then when it receives the input command history, it shows the records. 

Implemented an additional flag to the history command, which is the -sbu (SortByUsage). When a command input is history -sbu, the program  sorts the history commands by execution duration (end time – start time) in descending order. This means when the shell program executes any commands, it records the command execution time and store both the executed commands and its time information.

The other built-in command that the shell supports is exit, i.e. if the user inputs "exit" the shell program will exit.
