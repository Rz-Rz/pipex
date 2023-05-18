# Pipex: A Simple Implementation of Unix Pipes
Pipex is a simple program designed to illustrate the concept of Unix pipes and demonstrate a deep understanding of operating system programming.
The program emulates the behavior of a single pipe between two commands, as in the Unix shell command  ls | wc -l.

### Installation
Follow these steps to install:

1. **Clone the repository**:

Start by cloning the repository to your local machine. You can do this by running the following command in your terminal:
```bash
git clone https://github.com/Rz-Rz/pipex.git
```

2. **Navigate into the project directory**:
After you clone the repository, navigate into the project directory with this command:
```bash
cd pipex
```

3. **Compile the program**:
The next step is to compile the program. You can do this by running the make command in the project directory:
```bash
make
```

4. **Running the program**:
Once you've built the Pipex program, you can run it by using the following command:
```bash
./pipex infile cmd1 cmd2 outfile
```
In this command:

- **infile** is the name of the input file.
- **cmd1** and **cmd2** are the two commands you want to execute.
- **outfile** is the name of the output file.

5. **Run the bonus**:
The bonus part of Pipex allows handling multiple pipes and special redirections like here_doc (**<<**) and append (**>>**).
```bash
make bonus
```

To use Pipex with multiple commands, simply add more commands separated by pipes (|) in the command line:

```bash
./pipex_bonus infile cmd1 cmd2 cmd3 ... cmdn outfile
```

- **infile** is the name of the input file.
- **cmd1**, **cmd2**, **cmdn** are the commands you want to execute in a pipeline.
- **outfile** is the name of the output file.

6. **Using here_doc Redirection('<<') and append ('>>')**:
```bash
./pipex_bonus here_doc DELIMITER cmd1 cmd2 outfile
```
In this command:

- **DELIMITER** is the end token for the input string.
- **cmd1** and **cmd2** are the two commands you want to execute.
- **outfile** is the name of the output file.

```bash
./pipex_bonus here_doc EOF "grep world" "wc -l" outfile
```
This command will read input until it encounters **EOF**, then pipe the input containing **world** to** wc -l**, with **outfile** as the output. **Output** file will be opened in **append mode** and not truncate since we are using **here_doc mode**.


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

**Exit code meaning** :   
- `1` - Catchall for general errors
- `2` - Misuse of shell builtins (according to Bash documentation)
- `126` - Command invoked cannot execute
- `127` - “command not found”
- `128` - Invalid argument to exit
- `128+n` - Fatal error signal “n”
- `130` - Script terminated by Control-C
- `255\*` - Exit status out of range


**Understanding the importance of waiting for children :**  
The key is to have the parent always wait for all children process to finish. This is where the **wait**() and **waitpid**() system calls come into play. 
They allow a parent process to pause its execution and wait for one of its child processes to finish executing. When the child process finishes, it sends a SIGCHLD signal to its parent process. 
The parent process can then retrieve the child's exit status and proceed with its execution. But what happens if the parent process doesn't call wait() or waitpid()? 
The child process will finish its execution and send a SIGCHLD signal to its parent, but the parent won't be listening for it. 
The child process's entry will remain in the process table, and the process will become a zombie. This situation can be problematic because each entry in the process table takes up system resources. 
Linux systems have a finite number of process IDs — 32767 by default on 32-bit systems. Each zombie retains its process ID (PID).
If a system has many zombie processes, they can fill up the process table, preventing new processes from being created.  
This is known as a "zombie apocalypse" in Unix parlance. https://stackoverflow.com/questions/9361816/maximum-number-of-processes-in-linux

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

Of course before that we want to wait first for the last command the same way we showed earlier, with the corresponding pid and parse the status code to correctly assign a proper exit code. 

### Edge Cases  
These are key things to look for, we could call them the building blocks of pipex and unix inter system communication. It is easy to get them wrong.

1. **Parallel Execution** : Commands run in parallel, not sequentially. This allows the commands to process data as it becomes available, for example, the second command can start processing as soon as the first command produces some output. A good way to test if your architecture has been built for parallel execution is the following pipe command : **sleep 5 | sleep 5**. Your program should only sleep for a total of 5 second rather than 10 second total because both sleep command are **executed at the same time**.

2. **Command Execution Order** : Since all process run concurrently, when you run a command like **ls | cat**, you will get the output of ls, while the prompt is waiting for an input for the cat command. You must correctly close all end of a pipe both in the children and the parent once all duplication of file descriptor has been done. You can learn more about this behaviour here: https://stackoverflow.com/questions/75069068/how-can-i-understand-the-behavior-of-pipe-with-varying-data-flow?noredirect=1#comment132480674_75069068

3. **PATH Handling** : You must check if the path is not unset when running your program. The program must be robust enough to not segfault when PATH is unset, or the environment is missing (\*\*envp can be unset aswell with env -i). Also the program must still run command if path is missing but the absolute path of a command is provided. Example: **/usr/bin/ls** should work even if the path or environment is missing.

4. **Buffering** : The **yes | head** command demonstrates how Unix pipes use buffering. The yes command generates an infinite amount of output, but head only reads the first 10 lines. Because of the way buffering works, the yes command will stop producing output once the pipe's buffer is full and it will only continue when there's room in the buffer. This behavior is managed by the operating system's pipe implementation, and the size of the buffer can vary between different systems. To correctly reproduce this behavior you must make sure that you are correctly managing the pipe and the different file descriptor throughout the program execution.

### Computing History - Reason behind concurrent pipes
A good way to understand the reason behind pipe is to break down pipe into its most basic form. The following command :
```bash
A | B
```
Could easily be mistaken for being identical to :
```bash
A > temporary_file
B < temporary_file
rm temporary_file
```
But, back when Unix was created and children rode dinosaurs to school, disks were very small, and it was common for a rather benign command to consume all the free space in a file system.  If B was something like grep some_very_obscure_string, the final output of the pipeline could be much smaller than that intermediate file.  Therefore, the pipe was developed, not as a shorthand for the “run A first, and then run B with input from A’s output” model, but as a way for B to execute concurrently with A and eliminate the need for storing the intermediate file on disk.

### Testers for Pipex
https://github.com/Yoo0lh/pipex_tester_42  
https://github.com/vfurmane/pipex-tester  
https://github.com/gsilva-v/PipexTester  
https://github.com/denisgodoy/pipex-tester  

