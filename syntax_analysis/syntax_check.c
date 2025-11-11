/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:35:29 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 17:21:31 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int check_redir(t_token *current)
{
    if(!current->next)
        return(1);           
    if(current->next->type != TOKEN_WORD)
        return(1);
    return(0);
}

static int check_pipe(t_token *current, t_token *prev)
{
    
    if(current->type == TOKEN_PIPE)
    {
        if(!current->next || current->next->type != TOKEN_WORD)
            return(1);
        if(!prev || prev->type == TOKEN_PIPE || is_redirection(prev->type))
            return(1);
    }
    return(0);
}

int syntax_check(t_token **tokens)
{
    t_token *current;
    t_token *prev = NULL;

    if(tokens == NULL || *tokens == NULL)
        return(0);
    current = *tokens;
    if(!current->next)
        return(0);
    if(current->type == TOKEN_PIPE || current->type == TOKEN_UNKNOWN)
        return(0);
    while(current)
    {
        if(current->type == TOKEN_PIPE && check_pipe(current, prev))
            return(0);
        if(is_redirection(current->type) && check_redir(current))
            return(0);
        prev = current;
        current = current->next;
    }
    if(prev->type == TOKEN_PIPE || is_redirection(prev->type))
        return(0);
    return(1);
}
