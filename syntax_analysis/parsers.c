/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:03:58 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 17:21:31 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_redirection(t_token_type type)
{
    if(type == TOKEN_REDIR_IN)
        return(1);
    else if(type == TOKEN_REDIR_OUT)
        return(1);
    else if(type == TOKEN_APPEND)
        return(1);
    else if(type == TOKEN_HEREDOC)
        return(1);
    return(0);
}

t_node_type detect_redir_type(t_token *tokens)
{
    if(!tokens)
        return (NODE_INVALID); //made changes from agent

    if((tokens)->type == TOKEN_REDIR_IN)
        return(NODE_REDIR_IN);
    else if((tokens)->type == TOKEN_REDIR_OUT)
        return(NODE_REDIR_OUT);
    else if((tokens)->type == TOKEN_APPEND)
        return(NODE_APPEND);
    else if((tokens)->type == TOKEN_HEREDOC)
        return(NODE_HEREDOC);
    return(NODE_INVALID);
}

void append_redir(t_redir **redir_list, t_redir *new_redir)
{
    t_redir *tmp;
 
    if(!new_redir || !redir_list)
        return ;
    new_redir->next = NULL;
    if(!*redir_list)
    {
        *redir_list = new_redir;
        return;
    }
    tmp = *redir_list;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new_redir;
}

t_ast *parse_command(t_token **tokens)
{
    t_ast *command_node;
    t_redir *new_redir;
    t_redir *redir_list = NULL;
    t_node_type redir_type;

    if(!*tokens ||(*tokens)->type != TOKEN_WORD)
        return (NULL);
    
    command_node = create_command_node(tokens); //do i need to move tokens' pos;
    if(!command_node)
        return(NULL);
    while(*tokens && is_redirection((*tokens)->type))
    {
        if(!(*tokens)->next)
        {
            fprintf(stderr, "error: missing filename after redirection\n");
            return NULL;
        }
        redir_type = detect_redir_type(*tokens);
        if(redir_type == (t_node_type)-1)
        {
            fprintf(stderr, "error: unknown redirection type\n");
            return NULL;
        }
        new_redir = create_redir(redir_type, tokens);
        if(!new_redir)
            return (NULL);
        append_redir(&redir_list, new_redir); //poss-multiply - ADVANCING token pointer???
        //*tokens = (*tokens)->next->next;
    }
    command_node->redirections = redir_list;
    return(command_node);
}
