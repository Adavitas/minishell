/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:17:58 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/10/26 21:21:41 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int handle_operator(t_token **token_list, char *input)
{
    int len = 0;
    
    if((input[0] == '>' && input[1] == '>') ||
        (input[0] == '<' && input[1] == '<'))
        len = 2;
    else
        len = 1;
    
    char *operand = ft_substr(input, 0, len);
    add_token(token_list, TOKEN_OPERATOR, operand);
    free(operand);

    return(len);
}