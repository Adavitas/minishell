#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "tokenizer.h"
# include "parser.h"
# include "ast_types.h"

/* Command structure for execution */
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* Environment variable structure */
typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

/* Environment structure */
typedef struct s_env
{
	t_env_var	*vars;
	char		**envp_array;
}	t_env;

/* Global for signal handling */
extern int	g_signal_received;

/* ========== EXECUTOR ========== */
int			execute(t_cmd *cmds, t_env *env);
int			execute_ast(t_ast *ast, t_env *env);
char		*get_command_path(char *command, t_env *env);
void		execute_command(char **args, t_env *env);

/* ========== PIPELINE & REDIRECTIONS ========== */
int			execute_pipeline(t_cmd *cmds, t_env *env);
void		setup_redirections(t_redir *redirs);
int			open_infile(char *path);
int			open_outfile(char *path, int append);
int			handle_heredoc(char *delimiter);
void		handle_redir_in(t_redir *redir);
void		handle_redir_out(t_redir *redir, int append);
void		handle_heredoc_redir(t_redir *redir);

/* ========== AST HELPERS ========== */
void		setup_child_io(int fd_in, int fd_out);
void		restore_fds(int stdin_backup, int stdout_backup);
void		execute_ast_child(t_ast *node, t_env *env, int fd_in, int fd_out);
int			execute_builtin_ast(t_ast *node, t_env *env, int last_status);
int			execute_builtin_with_redirs_ast(t_ast *node, t_env *env,
				int last_status);
void		fork_left_child(t_ast *pipe_node, t_env *env, int fd_in,
				int pipefd[2]);
int			fork_right_child(t_ast *pipe_node, t_env *env, int fd_in,
				int pipefd[2]);
int			execute_pipe_node(t_ast *pipe_node, t_env *env, int fd_in);
int			execute_ast_recursive(t_ast *node, t_env *env, int fd_in,
				int fd_out);

/* ========== BUILTINS ========== */
int			is_builtin(char *cmd);
int			execute_builtin(t_cmd *cmd, t_env *env, int last_status);
int			builtin_echo(char **args);
int			builtin_cd(char **args, t_env *env);
int			builtin_pwd(void);
int			builtin_export(char **args, t_env *env);
int			builtin_unset(char **args, t_env *env);
int			builtin_env(t_env *env);
int			builtin_exit(char **args, int last_status);

/* ========== ENVIRONMENT ========== */
t_env		*init_env(char **envp);
char		*get_env_value(t_env *env, char *key);
void		set_env_value(t_env *env, char *key, char *value);
void		unset_env_value(t_env *env, char *key);
char		**env_to_array(t_env *env);
void		free_env(t_env *env);

/* ========== SIGNALS ========== */
void		setup_signals(void);
void		setup_child_signals(void);

/* ========== LEXER & PARSER ========== */
void		free_cmds(t_cmd *cmds);
char		*expand_vars(char *str, t_env *env, int last_status);
t_cmd		*parse(t_token *tokens, t_env *env, int last_status);

/* ========== UTILS ========== */
void		ft_error(char *msg, int code);
void		print_error(char *cmd, char *arg, char *msg);
int			ft_arraylen(char **array);
void		free_array(char **array);

#endif
