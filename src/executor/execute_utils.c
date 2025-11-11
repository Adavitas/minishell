#include "minishell.h"

static void	free_cmd_redirs(t_redir *redir)
{
	t_redir	*next_redir;

	while (redir)
	{
		next_redir = redir->next;
		free(redir->file);
		free(redir);
		redir = next_redir;
	}
}

static void	free_cmd_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		free_cmd_args(current->args);
		free_cmd_redirs(current->redirs);
		free(current);
		current = next;
	}
}

static int	execute_external(t_cmd *cmds, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		setup_redirections(cmds->redirs);
		execute_command(cmds->args, env);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	execute(t_cmd *cmds, t_env *env)
{
	if (!cmds || !cmds->args || !cmds->args[0])
		return (0);
	if (is_builtin(cmds->args[0]))
		return (execute_builtin(cmds, env, 0));
	return (execute_external(cmds, env));
}
