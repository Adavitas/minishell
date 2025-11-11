/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:13:44 by adavitas          #+#    #+#             */
/*   Updated: 2025/11/11 18:13:49 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env *env)
{
	t_env_var	*var;

	var = env->vars;
	while (var)
	{
		if (var->value)
			printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
	return (0);
}
