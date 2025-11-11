/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:12:57 by adavitas          #+#    #+#             */
/*   Updated: 2025/11/11 18:12:58 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_TYPES_H
# define AST_TYPES_H

# include "parser.h"

/* Forward declaration */
typedef struct s_env	t_env;

/* AST execution prototypes */
int		execute_ast(t_ast *ast, t_env *env);

#endif
