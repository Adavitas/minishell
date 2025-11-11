#include "minishell.h"

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	print_error("pwd", NULL, strerror(errno));
	return (1);
}
