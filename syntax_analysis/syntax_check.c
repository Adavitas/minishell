/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:35:29 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 16:21:22 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int check_redir(t_token *current)
{
    if(!current->next)
        return(1);           
    if(current->next->type != WORD)
        return(1);
    return(0);
}

static int check_pipe(t_token *current, t_token *prev)
{
    
    if(current->type == PIPE)
    {
        if(!current->next || current->next->type != WORD)
            return(1);
        if(!prev || prev->type == PIPE || is_redirection(prev->type))
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
    if(current->type == PIPE || current->type == UNKNOWN)
        return(0);
    while(current)
    {
        if(current->type == PIPE && check_pipe(current, prev))
            return(0);
        if(is_redirection(current->type) && check_redir(current))
            return(0);
        prev = current;
        current = current->next;
    }
    if(prev->type == PIPE || is_redirection(prev->type))
        return(0);
    return(1);
}
