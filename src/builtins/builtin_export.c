#include "minishell.h"

int	builtin_export(char **args, t_env *env)
{
	int	i;

	if (!args[1])
	{
		builtin_env(env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		printf("export: %s (not implemented yet)\n", args[i]);
		i++;
	}
	return (0);
}

int	builtin_unset(char **args, t_env *env)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		unset_env_value(env, args[i]);
		i++;
	}
	return (0);
}
