# mini_shell
creating our own shell (but mini)

### Branch organization
| Branch Names | Function |
| -------- | -------- |
| main     | all joined working code (need to pull request to join said working code from the feat-* branches)|
| feat-parse     | branch to develop the parsing feature    |
| feat-exec     | branch to develop the execution feature    |
| test-*     | branches starting in “test-” are for testing anything (can be deleted)    |

### <br>
### Allowed external functions

[more explanations of the fts (42 cursus)](https://42-cursus.gitbook.io/guide/rank-03/minishell/functions)
* **readline() _<stdio.h>_ -** functions in a similar way as get_next_line(1) but intead of recieving an fd it recieves a **const char \*prompt** that will be displayed idly in the terminal as the prompt

* **rl_clear_history() _<stdio.h>_ -** clears readline history i guess?

* **add_history() _<stdio.h>_ -** recieves **char \*s** and saves that string in the history (like up and down arrows)

* **sigaction() _<signal.h>_ -** change the action taken by a process when recieving a specific signal (man 7 signal)

* **sigemptyset() _<signal.h>_ -** bezero but for sigset_t

* **sigaddset() _<signal.h>_ -** add sig to sigset_t

* **kill() _<signal.h>_ -** add sig to sigset_t


<br>**rapid fire:**
* **printf, malloc, free, write, access, open, read, exit, execve, dup, dup2, pipe, strerror, perror**