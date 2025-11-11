/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:35:11 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 17:21:31 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast *parse_pipeline(t_token **tokens)
{
    t_ast *right;
    t_ast *left;
    t_ast *pipe_node;
    
    if(!tokens || !*tokens)
        return (NULL);
    left = parse_command(tokens); //consume initial command and words;
    if(!left)
        return (NULL);
    while(*tokens && (*tokens)->type  == TOKEN_PIPE)
    {
        *tokens = (*tokens)->next;
        right = parse_command(tokens);
        if(!right)
        {
            printf("syntax error");
            return(NULL);
        }
        pipe_node = create_pipe_node(NODE_PIPE, left, right); //create a pipe node linking left and right commands
        left = pipe_node;
    }
    return(left); //no pipe
}

t_ast *syntax_analysis(t_token **token_list)
{
    t_ast *ast_tree;
    
    if(!token_list)
        return NULL;
    if(!syntax_check(token_list))
        return NULL;
    ast_tree = parse_pipeline(token_list);
    return(ast_tree);
}
