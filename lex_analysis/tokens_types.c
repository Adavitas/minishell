/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:55:25 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 16:23:27 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int is_redirect(const char *str)
{
    if (!str || !*str)
        return (0);
    if (str[0] == '>' || str[0] == '<')
        return (1);
    return (0);
}

t_tokentype get_op_type(char *token)
{
    if(!token)
        return(WORD);
    if(ft_strcmp(token, "|") == 0)
        return(PIPE);
    else if(ft_strcmp(token, "<") == 0)
        return(REDIR_IN);
    else if(ft_strcmp(token, ">") == 0)
        return(REDIR_OUT);
    else if(ft_strcmp(token, ">>") == 0)
        return(APPEND);
    else if(ft_strcmp(token, "<<") == 0)
        return(HEREDOC);
    return(WORD); /*shells usually just treat unexpected sequences as words*/
}
