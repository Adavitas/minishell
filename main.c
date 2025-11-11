#include "minishell.h"

static int	process_line(char *line, t_env *env, int last_status)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		status;

	tokens = tokenize(line);
	if (!tokens)
		return (last_status);
	cmds = parse(tokens, env, last_status);
	free_tokens(tokens);
	if (!cmds)
		return (last_status);
	status = execute(cmds, env);
	free_cmds(cmds);
	return (status);
}

static int	handle_input(char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (0);
	}
	if (!*line)
		return (1);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	int		last_status;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	setup_signals();
	last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!handle_input(line))
			break ;
		if (*line)
		{
			add_history(line);
			last_status = process_line(line, env, last_status);
		}
		free(line);
	}
	free_env(env);
	rl_clear_history();
	return (last_status);
}
