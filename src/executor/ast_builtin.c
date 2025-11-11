#include "minishell.h"
#include "ast_types.h"

int	execute_builtin_ast(t_ast_node *node, t_env *env, int last_status)
{
	t_cmd	cmd_wrapper;

	cmd_wrapper.args = node->args;
	cmd_wrapper.redirs = node->redirs;
	cmd_wrapper.next = NULL;
	return (execute_builtin(&cmd_wrapper, env, last_status));
}

int	execute_builtin_with_redirs_ast(t_ast_node *node, t_env *env,
	int last_status)
{
	int		stdin_backup;
	int		stdout_backup;
	int		status;
	t_cmd	cmd_wrapper;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	setup_redirections(node->redirs);
	cmd_wrapper.args = node->args;
	cmd_wrapper.redirs = node->redirs;
	cmd_wrapper.next = NULL;
	status = execute_builtin(&cmd_wrapper, env, last_status);
	restore_fds(stdin_backup, stdout_backup);
	return (status);
}

void	execute_ast_child(t_ast_node *node, t_env *env, int fd_in, int fd_out)
{
	setup_child_signals();
	setup_child_io(fd_in, fd_out);
	setup_redirections(node->redirs);
	if (is_builtin(node->args[0]))
		exit(execute_builtin_ast(node, env, 0));
	else
		execute_command(node->args, env);
}
