
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
// If theres no CMD but REDIR exists vreate CMD node NULL and the REDIR stays in the left:
// EX: > outfile | > outfile
// -------------------------------------------------------------------------------------------------|

// CHECKS ERROR

// Check what is after here_doc, strncmp, if for redirs ou pipe Error the syntax
//	- Done
// If there is no space between quotes is considered 1 token: - Done
// Example: "easd"'O'""
// Get ridof len in working quotes and do a funciton that gets me the lenght in get word;
//	- Done
// Implement in split that needs to split spaces and tabs in the same String;
//	- Done
// This CMD:  >> banana cmd banana
// Needs to be REDIR ARG CMD ARG but is doing REDIR ARG ARG ARG
//	- I think is Done;
// In the tree the last node redir is over writig the prrevious ones;
// > file > | a - Syntax Error - done

// Reminder EXPANSIONS HERE_DOC:
// cat << $"$HOME" does not expand and the lim is $HOME
// if the LIM has a "" like EOf"f" it does not expand
// if the LIM is the expansion like $HOME it works as a lim and does not expand
// if is a normal LIM without any quotes it always expands
// DO a bolean to say if the lim had quotes; for the here_doc expansions

// REDIRS: not HERE_DOC
// If after redir there is an expansion ansd inside of said expansion there is more than one word
// the redir fails because of ambiguous redirect

// TAREFAS:
// 		// line = atuafuncao(line, limiter);
//	Take of exit in syntax error

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

// messages
# define M_HERE_EOF "warning: here-document delimited by end-of-file "
# define VAR_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define SHLVL_WARN \
	"warning: shell level (2147483647) too high, \
resetting to 1\n"

// ------------------------PARSING----------------------------

// TOKENS

void		tokenadd_back(t_token **tklst, t_token *newtk);
void		tokenadd_front(t_token **tklst, t_token *newtk);
t_token		*newtoken(char *cont);
t_token		*create_tokens(char *input);
bool		place_token(char *input, t_token **head);
void		print_tokens(t_token *tokens);
bool		is_token(t_token *token);
void		expand_token_list(t_token **head, t_minishell *ms);
t_token		*replace_expanded_token(t_token **head, t_token *curr,
				char **expanded);
t_token		*join_token_list(t_token **head, t_token *curr, t_token *first_new);

// TREE UTILS

void		print_tree(t_tree_node *tree_node, int depth, char *side);
void		tree_apply_print(t_tree_node *root, int depth, char *side);
t_tree_node	*newtreenode(t_node_cont cont);
t_tree_node	*create_tree(t_token **tokens, t_minishell *ms);
t_node_cont	assign_tree_cont(t_token *token);
void		if_command(t_token *tokens, t_tree_node *cmd_node);
void		place_treenode(t_token *tokens, t_tree_node **root, bool pipe);
void		free_tree_node_cont(t_node_cont cont);
void		free_tree(t_tree_node *tree_head);
void		tree_cont_init(t_node_cont *cont);
t_token		*iteri_till_pipe(t_token *token);
char		**tree_alloc_args(t_token *token);

// EXPANSIONS

char		**input_expander(char *input, t_minishell ms);
char		*process_quote_expansions(char *input, t_minishell ms,
				int *is_quote);
void		the_expansion(char *input, t_minishell ms, int *is_quote,
				char *result);
char		*expansion(char *input, char **env);
void		expand_single_quotes(char *input, char *result, int *i);
void		expand_double_quotes(char *input, char *result, int *i,
				t_minishell ms);
void		expand_unquotes(char *input, char *result, int *i, t_minishell ms);
void		expansion_exit_status(char *result, int *i, char *exit_status);
char		*get_search(char *input);
size_t		the_length(char *input, t_minishell ms);
size_t		len_expansion(char *input, char **env);
size_t		len_double_quotes(char *input, char **env, int *i, int exit_status);
size_t		len_single_quote(char *input, int *i);
size_t		len_unquoted(char *input, char **env, int *i, int exit_status);
void		len_exit_status(char *exit_status, size_t *len, int *i);
char		**separator_3000(char *expanded, int is_quote);
char		**separate(char *expanded);
char		*quote_remover(char *s);
char		*quote_limiter(char *exp);
size_t		quote_conter_len(char *s);
char		*my_function(t_minishell ms, char *line, char *limiter, t_tree_node *node);

// ASSIGN TYPES

void		assign_type_token(t_token *token, bool exp);
void		assign_name(int type);
void		assigns_types(t_token *token, bool exp);
void		assigns_cmd(t_token *head, bool exp);
void		assigns_built_in(t_token *token);
void		is_limtiter_or_arg(t_token **temp);

// UTILS

char		*add_spaces(char *input);
int			space_length(char *input);
char		*space_put(char *input, int len);

// CHECKS

bool		check_quotes(char *input);
void		master_check(t_token **token);
void		syntax_clear(t_token *token);
char		*check_expansion(char *input);
size_t		checked_len(char *input);

// ERRORS

void		ft_error_check(t_token **token);

// SPLIT UTILS

char		**cracked_split(char const *s);
int			word_len(char const *s);
int			skip_quote(const char *s);
void		word_runner(const char **s);
bool		is_sep(char c);

// FAKE

char		*fake_readinput(t_minishell ms, char *input);
t_tree_node	*fake_create_tree(t_token *tokens);
void		fake_clear_token_lst(t_token *token);

// --------------------------EXECUTION--------------------------

// STRUCT INIT

void		minishell_struct_init(t_minishell *ms, char **env);

// GENERAL UTILS

void		minishell_clean(t_minishell minishell, int status);
void		process_waiting(int proc_n, int *ids, int *status);
void		master_close(void);
void		error_msg_status(char *message, int *status, int value);

// SIGNALS
void		init_sigact(t_minishell *minishell, int flag);

// MATRIX UTILS

char		**matrix_add_to_index(char **env, char *add, size_t idx,
				size_t len);
char		**matrix_add_front(char *add, char **original);
size_t		ft_matrixlen(char **matrix);
char		**matrix_dup_char(char **original_matrix);

// NEW LIBFT

int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(char *src, size_t n);
int			ft_iswhitespace(int c);

// MATRIX QUICK SORT

char		**sort_matrix(char **original, int len);
void		ft_string_swap(char **a, char **b);

// DISTRIBUTER

void		master_distributer(t_minishell *ms, t_tree_node *node);
void		command_process(t_minishell *ms, t_tree_node *node);
void		cmd_parse_and_exe(t_minishell ms, t_tree_node *node, int *redir);
void		built_in_process(t_minishell *ms, t_tree_node *node);
void		built_in_exe(t_minishell *ms, t_tree_node *node, int out);

// REDIR HANDLER

void		redir_handler(t_minishell *ms, t_tree_node *node, int *in,
				int *out);
int			cmd_redir_executer(t_minishell *ms, t_tree_node *node, int *in,
				int *out);
int			successful_redir_check(int *in, int *out, int hd);
void		safe_close(int fd);

// HERE DOC

void		multi_here_doc_handler(t_minishell ms, t_pipe_data *pdata);
void		single_here_doc_handler(t_minishell ms, t_tree_node *pin, int *in);

// PIPE PROCESS

void		pipe_process(t_minishell *minishell, t_tree_node *node);

// PIPE CHILD PROCESS

void		assign_pipe_fds(t_minishell ms, t_pipe_data *pdata, int *redir_fd,
				int idx);
char		*get_path(t_minishell minishell, char *cmd);
int			error_code_for_exec(char *path);

// ECHO

void		echo_built_in(t_minishell *ms, t_tree_node *node, int fd);

// DIRECTORY (CD, PWD)

void		cd_built_in(t_minishell *ms, t_tree_node *node);
void		pwd_built_in(t_minishell *ms, t_tree_node *node, int fd);

// EXPORT

void		export_built_in(t_minishell *ms, t_tree_node *node, int fd);

// EXPORT UTILS

void		export_append(t_minishell *ms, int idx, char *new);
int			replace_env_value(t_minishell *ms, char *key, char *new, int idx);
void		move_env_var(t_minishell *ms, int *old_idx, int new_idx);

// GET ENV

char		*get_env(char *search, char **env);
int			get_env_idx(char **env, char *search);
char		*get_export_key(char *var);
char		*get_export_value(char *var);
int			env_elem_len(char *var, int key_flag);

// UNSET

void		unset_built_in(t_minishell *ms, t_tree_node *node);
void		remove_env_var(t_minishell *ms, size_t idx, size_t len);

// ENV

void		env_built_in(t_minishell *ms, t_tree_node *node, int fd);
void		print_env(t_minishell minishell, int export_flag, int fd);

// EXIT

void		exit_built_in(t_minishell *ms, t_tree_node *node);
int			long_check(char *argv, long *arg_n);

#endif // MINISHELL_H