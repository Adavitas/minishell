#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, int last_status)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
		exit(last_status);
	if (!is_numeric(args[1]))
	{
		print_error("exit", args[1], "numeric argument required");
		exit(255);
	}
	if (args[2])
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	exit_code = ft_atoi(args[1]) % 256;
	if (exit_code < 0)
		exit_code += 256;
	exit(exit_code);
}
