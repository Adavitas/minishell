/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:10:37 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 23:05:15 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char **store_avs(t_token **tokens)
{
    if(!tokens || !*tokens)
        return (NULL);
    int  i;
    int count = 0;
    t_token *tmp;
    char **av;
    tmp = *tokens;
    while(tmp && tmp->type == TOKEN_WORD)
    {
        count++;
        tmp = tmp->next;
    }
    av = malloc(sizeof(char *) * (count + 1));
    if(!av)
        return(NULL);
    i = 0;
    while(*tokens && (*tokens)->type == TOKEN_WORD)
    {
        av[i++] = ft_strdup((*tokens)->value);
        *tokens = (*tokens)->next;
    }
    av[i] = NULL;
    return(av);
}

t_ast *create_ast_node(t_node_type type)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if(!node)
        return(NULL);
    node->type = type;
    node->argv = NULL;
    node->redirections = NULL;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

t_ast *create_command_node(t_token **tokens)
{
    t_ast *cmd_node;
    char **arr;

    if(!tokens || !*tokens)
        return (NULL);
    cmd_node = create_ast_node(NODE_COMMAND);
    if(!cmd_node)
        return(NULL);
    arr = store_avs(tokens);
    if(!arr)
    {
        free(cmd_node);
        return(NULL);
    }
    cmd_node->argv = arr;
    return(cmd_node);
}

t_redir *create_redir(t_node_type type, t_token **tokens)
{
    t_redir *redir_node;

    if(!tokens || !*tokens || !(*tokens)->next)
        return (NULL);
    redir_node = malloc(sizeof(t_redir));
    if(!redir_node)
        return (NULL);
    redir_node->type = type;
    redir_node->filename = ft_strdup((*tokens)->next->value);
    if(!redir_node->filename)
    {
        free(redir_node);
        return(NULL);
    }
    redir_node->next = NULL;
    *tokens = (*tokens)->next->next; //skip operator and filename;
    return(redir_node);
}

t_ast *create_pipe_node(t_node_type type, t_ast *left, t_ast *right)
{
    t_ast *pipe_node = create_ast_node(type);
    if(!pipe_node)
        return (NULL);
    pipe_node->type = type;
    pipe_node->argv = NULL;
    pipe_node->redirections = NULL;
    pipe_node->left = left;
    pipe_node->right = right;
    return(pipe_node);
}