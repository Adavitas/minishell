#include "minishell.h"

static int	is_valid_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n' && arg[i] != 'e' && arg[i] != 'E')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

static int	has_n_flag(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'n')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_valid_flag(args[i]))
	{
		if (has_n_flag(args[i]))
			newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
