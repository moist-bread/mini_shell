
#ifndef MINISHELL_H
# define MINISHELL_H

// NOTES: ANDRE

// char *input = "< infile cat | cat | "ls -l" > out";
// cracked slpit returns t_node just for basic token and sep is space.
// Nodes:
// 1 - "<"; 2 - "infile"; 3 - "cat"; 4 - "|"; 5 - "cat"; etc;
// funcs that check the new list of tokens.
// Funcs:
// Check Pipes and redir for spaces,
// if they
//	dont have it put space after and before
// Diverse check enquanto corro a lista the tokens;
// Assign types to the tokens;
// Func That will create the tree for varios Casos;

// -------------------------------------------------------------------------------------------------|

// First pipe initilize pipe data and put number of cmds.
// Other pipes just the type and the correspondant left and right nodes;
// If Pipe, Left always cmds;
// If Pipe, Right next Operator or The final cmds;
// If Cmd, Left Redir, Right Args "Flags e afins"
// If Redir, Left Redir, cont the file name or LIMITER,
// Consult on the .h for the Types of Redir;
// Check with rackel if is Build it for the correct Type;
// If There Redir, Right is Arg, Check if next after Arg is Redir.
// If is Redir do the normal, if not check if is Pipe,
// If is Pipe start over.
// -------------------------------------------------------------------------------------------------|

// CHECKS ERROR

// Check what is after here_doc, strncmp, if for redirs ou pipe Error the syntax
// If there is no space between quotes is considered 1 token:
// Example: "easd"'O'""
// Get ridof len in working quotes and do a funciton that gets me the lenght in get word;
// Implement in split that needs to split spaces and tabs in the same String;

// -------------------------------------------------------------------------------------------------|

// LIBS
# include "Libft/libft.h"
# include "ms_structs.h"
# include <curses.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

// DEFINES
// colors
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define CYN "\e[0;36m"
# define DEF "\e[0m"

// PARSING

void		tokenadd_back(t_token **tklst, t_token *newtk);
void		tokenadd_front(t_token **tklst, t_token *newtk);
t_token		*newtoken(char *cont);
t_token		*create_tokens(char *input);
char		*readinput(char *input);
void		place_token(char *input, t_token **head);
void		print_tokens(t_token *tokens);
void		assign_type_token(t_token *token);
void		assign_name(int type);
void		assigns_types(t_token *token);
void		assigns_built_in(t_token *token);
void		assigns_cmd_or_arg(t_token *token);
char		*add_spaces(char *input);
int			space_length(char *input);
char		*space_put(char *input, int len);
void		check_quotes(char *input);
void		clear_token_lst(t_token *token);
void		ft_error_check(t_token *token);
void		master_check(t_token *token);
bool		is_token(t_token *token);
char		*merge_adjacent_segments(char *input);
void		check_double_pipe(int *j, int *i, char *dest);
// void	checks_here_doc(t_token	*token);
// char	**cracked_split(char const *s, char c);
// void	working_quote(char const *s, int *len, char c);
// char	*extract_single_quote(const char *s, int len);
// int		handle_single_quote(const char **s);

// TREE UTILS

t_tree_node	*newtreenode(t_node_cont cont);
void		free_tree_node_cont(t_node_cont cont);
void		free_tree(t_tree_node *tree_head);
void		tree_cont_init(t_node_cont *cont);

// STRUCT INIT

void		minishell_struct_init(t_minishell *minis, char **env);

// MATRIX UTILS

char		**matrix_add_to_index(char **env, char *add, size_t idx,
				size_t len);
char		**matrix_add_front(char *add, char **original);
size_t		ft_matrixlen(char **matrix);
char		**matrix_dup_char(char **original_matrix);

// PIPE PROCESS

void		pipe_process(t_minishell *minishell, t_pipe_data *pdata);
void		read_and_exe_pipe_tree(t_minishell minishell,
				t_tree_node *tree_head, t_pipe_data *pdata, int idx);
void		setup_pipe_cmd(t_minishell minishell, t_tree_node *cmd_node,
				t_pipe_data *pdata, int idx);
void		process_waiting(int proc_n, int *ids, int *status);
void		minishell_clean(t_minishell minishell, int status);

// REDIR HANDLER

void		redir_handler(t_minishell minishell, t_tree_node *node, int *in,
				int *out);
void		master_close(void);

// PIPE CHILD PROCESS

void		assign_pipe_fds(t_minishell ms, t_pipe_data *pdata, int *redir_fd,
				int idx);
void		child_parse_and_exe(t_minishell ms, t_tree_node *node,
				t_pipe_data *pdata);
char		*get_path(t_minishell minishell, char *cmd);
int			error_code_for_exec(char *path);

// EXPORT

void		export_built_in(t_minishell *ms, t_tree_node *node);
void		print_env(t_minishell minishell, int export_flag);
int			invalid_export(char *arg);
void		export_distribute(t_minishell *ms, char *arg, char *key);

// GET ENV

char		*get_env(char *search, char **env);
int			get_env_idx(char **env, char *search);
char		*get_export_key(char *var);
char		*get_export_value(char *var);
int			env_elem_len(char *var, int key_flag);

// EXPORT UTILS

void		export_append(t_minishell *ms, int idx, char *new);
void		replace_env_value(t_minishell *ms, char *key, char *new, int idx);
void		move_env_var(t_minishell *ms, int *old_idx, int new_idx);

// NEW LIBFT

int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(char *src, size_t n);
int			ft_iswhitespace(int c);

// MATRIX QUICK SORT

char		**sort_matrix(char **original, int len);
void		ft_string_swap(char **a, char **b);

// ENV UTILS

void		unset_built_in(t_minishell *ms, t_tree_node *node);
void		remove_env_var(t_minishell *ms, size_t idx, size_t len);
void		echo_built_in(t_minishell *ms, t_tree_node *node);
void		env_built_in(t_minishell *ms, t_tree_node *node);

// EXIT

void		exit_built_in(t_minishell *ms, t_tree_node *node);
int			long_check(char *argv, long *arg_n);

// DISTRIBUTER

int			master_distributer(t_minishell *ms, t_tree_node *node);
void		command_process(t_minishell *ms, t_tree_node *node);
void		cmd_parse_and_exe(t_minishell ms, t_tree_node *node, int *redir);
void		pwd_built_in(t_minishell *ms, t_tree_node *node);
void		cd_built_in(t_minishell *ms, t_tree_node *node);

#endif // MINISHELL_H