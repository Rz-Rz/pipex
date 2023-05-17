# Pipex: A Simple Implementation of Unix Pipes
Pipex is a simple program designed to illustrate the concept of Unix pipes and demonstrate a deep understanding of operating system programming.
The program emulates the behavior of a single pipe between two commands, as in the Unix shell command  ls | wc -l.

### Understanding Unix Pipes
A pipe is a form of redirection in Unix systems that allows the output of one command to be used as the input of another. Pipes allow for data to be shared directly between programs without the need for temporary files or buffers.
In Unix, the pipe operator is represented by the vertical bar |. For example, in the command ls | cat, the ls command lists the contents of the current directory, and the cat command reads this list from the ls command's output instead of a file.

### Implementation Details
The Pipex program uses several key Unix system calls, such as fork, dup2, execve, and pipe, to emulate the behavior of a pipe. Here's a brief overview of how the program works:

1. **Forking**: The program creates two child processes using the fork system call. Each child process will execute one of the commands.

2. **Piping**: The pipe system call is used to create a pipe, which is a unidirectional data channel that can be used for interprocess communication.

3. **Duplication**: The dup2 system call is used to duplicate file descriptors, effectively redirecting the standard input and output. For the first command, the standard output is redirected to the write end of the pipe. For the second command, the standard input is redirected from the read end of the pipe.

4. **Execution**: Finally, the execve system call replaces the current process image with a new one -- the command to be executed. For the first child process, this will be the first command, and for the second child process, this will be the second command.

The program also takes care to close any unused file descriptors, a crucial step to prevent file descriptor leaks.

### Error Handling
In this project we are allowed to use the following function for error handling : **perror** and **strerror**.
- The **perror**() function displays the string you pass to it, followed by a colon, a space, and then the textual representation of the current errno value.
```C
void perror(const char *str);
```
- The **strerror**() function, which returns a pointer to the textual representation of the current errno value.
```C
char *strerror(int errnum);
```
Both of these function works with the global variable **errno**. To correctly use it you must first include the following header file : **errno.h**.
- The **errno** is set to zero at program startup. **Certain functions of the standard C library** (such as fork, pipe, dup2...) modify its value to other than zero to signal some types of error. 
You can also modify its value or reset to zero at your convenience.

Using it allows us to provide robust error handling to our program when using standard library function. 

**Program exit status.**
When reproducing correctly bash behaviour when running pipes, we have to handle pipeline exit status. The exit status of a pipeline is always the last command.
For a simple implementation of a pipe between to commands, we can use the following : 

- First save the pid of both fork. 
```C
pipex->children1 = fork();
pipex->children2 = fork();
```

- Then launch both commands and wait for them after they have been launched. When waiting for the last command, you can pass the status int ptr to get the exit code of the last command.
```C
waitpid(pipex.children1, NULL, 0);
waitpid(pipex.children2, **&pipex.status**, 0);
```

- Finally that exit code must be parsed into a meaningfull exit code using **Process Completion Macros**. They provide a way to interpret the status code provided by wait and waitpid.
**WIFEXITED(status)**: This macro checks if the child process terminated normally. A child process is considered to have terminated normally if it exits using the exit() or _exit() system calls, or if it returns from the main() function. This macro will return a non-zero value if the child process terminated normally.

**WEXITSTATUS(status)**: This macro should be used if WIFEXITED returned a non-zero value, meaning the process exited normally. It will return the exit status of the child process. This is the value that the process passed to exit() or _exit(), or the value that it returned from main().

**WIFSIGNALED(status)**: This macro checks if the child process was terminated by a signal. Signals are a way for processes to be notified of asynchronous events, and certain signals can cause a process to terminate. If the child process was terminated by a signal, this macro will return a non-zero value.

**WTERMSIG(status)**: This macro should be used if WIFSIGNALED returned a non-zero value, meaning the process was terminated by a signal. It will return the number of the signal that caused the termination. This can be useful for debugging or logging purposes, as it allows you to determine which signal caused the process to terminate.

**WIFSTOPPED(status)**: This macro checks if the child process was stopped by a signal. A stopped process is one that has been paused and can be resumed later. This is different from a terminated process, which has finished executing. If the child process was stopped by a signal, this macro will return a non-zero value.

**WSTOPSIG(status)**: This macro should be used if WIFSTOPPED returned a non-zero value, meaning the process was stopped by a signal. It will return the number of the signal that caused the process to stop. This can be useful for debugging or logging purposes, as it allows you to determine which signal caused the process to stop.

Here's my implementation:

```C
int	exit_macro(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	else
		return (EXIT_FAILURE);
}
```

**Understanding the importance of waiting for children :**
The key is to have the parent always wait for all children process to finish. This is where the **wait**() and **waitpid**() system calls come into play. 
They allow a parent process to pause its execution and wait for one of its child processes to finish executing. When the child process finishes, it sends a SIGCHLD signal to its parent process. 
The parent process can then retrieve the child's exit status and proceed with its execution. But what happens if the parent process doesn't call wait() or waitpid()? 
The child process will finish its execution and send a SIGCHLD signal to its parent, but the parent won't be listening for it. 
The child process's entry will remain in the process table, and the process will become a zombie. This situation can be problematic because each entry in the process table takes up system resources. 
Linux systems have a finite number of process IDs — 32767 by default on 32-bit systems. Each zombie retains its process ID (PID).
If a system has many zombie processes, they can fill up the process table, preventing new processes from being created.  
This is known as a "zombie apocalypse" in Unix parlance.

**Handling the bonus status exit**
Now to deal with an undefined number of pipes. One of the easy tricks to wait for all process to finish is the following:
```C
while (waitpid(0, NULL, 0) != -1)
	;
```
This line of code represents a loop that continues to execute as long as the **waitpid**() system call returns a value not equal to -1. In the context of Unix-based systems, **waitpid**() is a system call that's used for making a parent process wait until one of its child processes exits.
The **waitpid**() system call takes three parameters. The first one is the process ID (pid) of the child process that the parent process should wait for. A pid of 0 means that the parent process should wait for any of its child processes to exit.
The second parameter of waitpid() is a pointer to an integer where the exit status of the child process will be stored. In this case, NULL is passed as the second parameter, indicating that the parent process is not interested in the exit status of the child process. This is common when the parent process only needs to ensure that all child processes have finished, without needing to know how they finished.
The third parameter of waitpid() is used to modify the behavior of the system call. A value of 0 means that the waitpid() call will block, i.e., it will cause the parent process to pause its execution until a child process exits.

