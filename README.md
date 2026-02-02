Custom Unix Shell in C

Overview

This project is a custom Unix-like shell written in C, built to understand how real shells (such as bash) interact with the operating system. The shell reads user input, parses commands, executes built-in commands, and launches external programs using POSIX system calls.

The focus of this project was learning process control, execution flow, and shell design at the OS level.

⸻

Features
	•	Interactive shell prompt
	•	Command parsing and tokenization
	•	Execution of external commands using fork and execvp
	•	Built-in commands executed in the parent shell:
	•	cd
	•	exit
	•	pwd
	•	echo
	•	export
	•	unset
	•	PATH-based command resolution
	•	Proper parent/child synchronization using waitpid
	•	Robust error handling using errno
	•	Safe dynamic memory allocation and cleanup

⸻

Design Summary

The shell follows a classic read–execute loop:
	1.	Read a full line of input using getline
	2.	Parse the line into a command structure
	3.	Execute built-in commands directly in the shell process
	4.	Fork and execute external commands in a child process
	5.	Wait for the child to finish and clean up memory
  6.  Repeat

Built-in commands run before forking, since they modify shell state (working directory, environment variables).

⸻

What I Learned
	•	How Unix processes are created and managed (fork, exec, waitpid)
	•	How shells resolve executables using the PATH environment variable
	•	Proper handling of system call errors with errno
	•	Dynamic memory management patterns in C
	•	The difference between shell behavior and simply launching programs

This project helped solidify my understanding of how user-space programs interface with the operating system.


Build & Run
Simple! just type these lines in your terminal

1. make
2. ./mysh
3. make clean


Example of Code Functioning

mysh> pwd
/Users/raoul/project
mysh> cd src
mysh> ls
parser.c tokenizer.c executer.c
mysh> exit

Future Improvements
	•	Support for pipes (|) to allow chaining commands between processes
	•	Input/output redirection (>, <, >>) using file descriptors
	•	Signal handling for interactive use (Ctrl+C, Ctrl+Z)
	•	Improved parsing support for quoting and escaping
	•	Command history and line editing support



