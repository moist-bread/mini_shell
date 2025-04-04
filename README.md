# $\color{LightSkyBlue}{\textbf{Mini Shell}}$
creating our own shell (but mini)

### Branch organization
| Branch Names	| Function			|
| --------		| --------			|
| main			| all joined working code (requires pull request to merge from the feat-* branches)|
| feat-parse	| branch to develop the parsing feature		|
| feat-exec		| branch to develop the execution feature	|
| test-*		| branches starting in “test-” are for testing anything (can be deleted)	|

### <br>
### $\color{LightSkyBlue}{\textbf{Allowed external functions}}$

[more explanations of the fts (42 cursus)](https://42-cursus.gitbook.io/guide/rank-03/minishell/functions)

* $\color{DodgerBlue}{\textbf{readline()}}$ $\color{DarkCyan}{\textit{<readline/readline.h><readline/history.h>}}$ &nbsp; - functions in a similar way as get_next_line(1) but intead of recieving an fd it recieves a **const char \*prompt** that will be displayed idly in the terminal as the prompt

* ```rl_clear_history()``` $\color{DarkCyan}{\textit{<readline/history.h>}}$ &nbsp; - clears the command history created by readline (being able to up arrow and show the prev line)

* ```rl_on_new_line()``` $\color{DarkCyan}{\textit{<readline/history.h>}}$ &nbsp; - tells that we have moved onto a new empty line, usually used after outputting a line

* ```rl_replace_line()``` $\color{DarkCyan}{\textit{<readline/history.h>}}$ &nbsp; - replaces the current line with **char \*replacement**

* ```rl_redisplay()``` $\color{DarkCyan}{\textit{<readline/history.h>}}$ &nbsp; - replaces the current line with **char \*replacement**

* ```add_history()``` $\color{DarkCyan}{\textit{<stdio.h>}}$ &nbsp; - recieves **char \*s** and saves that string in the history (like up and down arrows)

* $\color{DodgerBlue}{\textbf{sigaction()}}$ _<signal.h>_ &nbsp; - change the action taken by a process when recieving a specific signal (man 7 signal)

* $\color{DodgerBlue}{\textbf{sigemptyset()}}$ _<signal.h>_ &nbsp; - bezero but for sigset_t

* $\color{DodgerBlue}{\textbf{sigaddset()}}$ _<signal.h>_ &nbsp; - add sig to sigset_t

* $\color{DodgerBlue}{\textbf{kill()}}$ _<signal.h>_ &nbsp; - sends signal **int sig** to process **pid_t pid**

* $\color{DodgerBlue}{\textbf{getcwd()}}$ _<unistd.h>_ &nbsp; - returns string of the absolute path of the current working directory and via **char \*buf** if present. if sent **size_t size** == 0 it allocs needed size  

* $\color{DodgerBlue}{\textbf{chdir()}}$ _<unistd.h>_ &nbsp; - change into the **char \*path** directory, returns -1 when failure

* $\color{DodgerBlue}{\textbf{stat()}}$ _<sys/stat.h>_ &nbsp; -  places information about the file from  **const char \*pathname** in **struct stat \*statbuf** 

* $\color{DodgerBlue}{\textbf{lstat()}}$ _<sys/stat.h>_ &nbsp; - same as stat but if the file is a symbolic link the information is about the link itself

* $\color{DodgerBlue}{\textbf{fstat()}}$ _<sys/stat.h>_ &nbsp; - same as stat but instead of a pathname it recieves a file descriptor

* $\color{DodgerBlue}{\textbf{unlink()}}$ _<unistd.h>_ &nbsp; - removes a link to the **const char \*path** file. when the link count is 0, and no process has it open, the file is freed

* $\color{DodgerBlue}{\textbf{opendir()}}$ _<dirent.h>_ &nbsp; - opens a directory stream (all files and dirs in **const char \*name**) and returns a pointer to it that is a **DIR \***

* $\color{DodgerBlue}{\textbf{readdir()}}$ _<dirent.h>_ &nbsp; - returns a **struct dirent \*** representing the next directory entry in the recieved **DIR \*dirp**

* $\color{DodgerBlue}{\textbf{closedir()}}$ _<dirent.h>_ &nbsp; - close but for **DIR \*** instead of file descriptors

* $\color{DodgerBlue}{\textbf{isatty()}}$ _<unistd.h>_ &nbsp; - sees if **int fd** is the file descriptor of a terminal. returns 1 if true, 0 is false

* $\color{DodgerBlue}{\textbf{ttyname()}}$ _<unistd.h>_ &nbsp; - returns a **char \*** of the path of the terminal device that is open on the **int fd**

* $\color{DodgerBlue}{\textbf{ttyslot()}}$ _<unistd.h>_ &nbsp; - returns the index of the controlling terminal of the calling process in the file /etc/ttys or on System  V-like systems it returns the current user's index in the user accounting data base (0 or -1 on error)

* $\color{DodgerBlue}{\textbf{ioctl()}}$ _<sys/ioctl.h>_ &nbsp; - control input output, can be used to know window size etc

* $\color{DodgerBlue}{\textbf{getenv()}}$ _<stdlib.h>_ &nbsp; - searches for parameter **const char \*name** in the env and returns the corresponding line if found 

* $\color{DodgerBlue}{\textbf{tcsetattr()}}$ _<termios.h>_ &nbsp; - sets the parameters associated  with  the  terminal adressed by the **int fd** according to the termios structure **const struct termios \*termios_p**

* $\color{DodgerBlue}{\textbf{tcgetattr()}}$ _<termios.h>_ &nbsp; - gets the parameters associated  with  the  terminal adressed by the **int fd** and stores it in the termios structure **struct termios \*termios_p**

* $\color{DodgerBlue}{\textbf{tgetent()}}$ _<termios.h>_ &nbsp; - sets the parameters associated  with  the  terminal adressed by the **int fd** according to the termios structure **const struct termios \*termios_p**

* $\color{DodgerBlue}{\textbf{tgetent()}}$ _<term.h><curses.h>_ &nbsp; -  loads the entry for name (conversion aid for programs that use the termcap library)

* $\color{DodgerBlue}{\textbf{tgetflag()}}$ _<term.h><curses.h>_ &nbsp; - gets the boolean entry for id, or zero if it is not available

* $\color{DodgerBlue}{\textbf{tgetnum()}}$ _<term.h><curses.h>_ &nbsp; - gets the numeric entry for id, or -1 if it is not available

* $\color{DodgerBlue}{\textbf{tgetstr()}}$ _<term.h><curses.h>_ &nbsp; - returns the string entry for id, or zero if it is not available

* $\color{DodgerBlue}{\textbf{tgoto()}}$ _<term.h><curses.h>_ &nbsp; -  instantiates the parameters into the given capability. The output from this routine is to be passed to **tputs()**

* $\color{DodgerBlue}{\textbf{tputs()}}$ _<term.h><curses.h>_ &nbsp; -   applies padding information (i.e., by interpreting marker embedded in the terminfo capability) and outputs it

<br>
<details>
<summary> Function use examples and prototypes:</summary>
<br>

* **char \*readline (const char \*prompt);** 
	```		c
	char *ret = readline("(Prompt) Your input goes here: ");
	if (ret == NULL)
		// EOF on empty line (CTRL + D)
	else
		printf("input collected: %s", ret);
	```

* **void rl_clear_history(void);** 

* **void rl_clear_history(void);** 

* **add_history() _<stdio.h>_ -** recieves **char \*s** and saves that string in the history (like up and down arrows)

* **sigaction() _<signal.h>_ -** change the action taken by a process when recieving a specific signal (man 7 signal)

* **sigemptyset() _<signal.h>_ -** bezero but for sigset_t

* **sigaddset() _<signal.h>_ -** add sig to sigset_t

* **kill() _<signal.h>_ -** sends signal **int sig** to process **pid_t pid**

* **getcwd() _<unistd.h>_ -** returns string of the absolute path of the current working directory and via **char \*buf** if present. if sent **size_t size** == 0 it allocs needed size  

* **int chdir(const char \*path);** 
	```		c
	int ret = chdir("Inc/libft");
	if (ret == -1)
		// error
	if (ret == 0)
		// success
	```
</details>

<br>**rapid fire:**
* **printf, malloc, free, write, access, open, read, exit, execve, dup, dup2, pipe, strerror, perror**