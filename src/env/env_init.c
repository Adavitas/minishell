/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 00:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2025/11/11 18:14:21 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_var	*create_env_var(char *key, char *value)
{
	t_env_var	*var;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	var->next = NULL;
	if (!var->key || !var->value)
	{
		free(var->key);
		free(var->value);
		free(var);
		return (NULL);
	}
	return (var);
}

static void	add_env_var(t_env *env, char *entry)
{
	char		*equal_sign;
	char		*key;
	char		*value;
	t_env_var	*new_var;
	t_env_var	*current;

	equal_sign = ft_strchr(entry, '=');
	if (!equal_sign)
		return ;
	key = ft_substr(entry, 0, equal_sign - entry);
	value = ft_strdup(equal_sign + 1);
	new_var = create_env_var(key, value);
	free(key);
	free(value);
	if (!new_var)
		return ;
	if (!env->vars)
		env->vars = new_var;
	else
	{
		current = env->vars;
		while (current->next)
			current = current->next;
		current->next = new_var;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->vars = NULL;
	env->envp_array = NULL;
	i = 0;
	while (envp[i])
	{
		add_env_var(env, envp[i]);
		i++;
	}
	env->envp_array = env_to_array(env);
	return (env);
}
