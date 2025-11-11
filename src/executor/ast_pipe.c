#include "minishell.h"
#include "ast_types.h"

void	fork_left_child(t_ast_node *pipe_node, t_env *env, int fd_in,
	int pipefd[2])
{
	pid_t	pid_left;

	pid_left = fork();
	if (pid_left == 0)
	{
		close(pipefd[0]);
		execute_ast_recursive(pipe_node->left, env, fd_in, pipefd[1]);
		exit(0);
	}
}

int	fork_right_child(t_ast_node *pipe_node, t_env *env, int fd_in,
	int pipefd[2])
{
	pid_t	pid_right;
	int		status;

	pid_right = fork();
	if (pid_right == 0)
	{
		close(pipefd[1]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		execute_ast_recursive(pipe_node->right, env, pipefd[0],
			STDOUT_FILENO);
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	waitpid(pid_right, &status, 0);
	return (status);
}

int	execute_pipe_node(t_ast_node *pipe_node, t_env *env, int fd_in)
{
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
	{
		print_error("pipe", NULL, strerror(errno));
		return (1);
	}
	fork_left_child(pipe_node, env, fd_in, pipefd);
	status = fork_right_child(pipe_node, env, fd_in, pipefd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
