/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:55:16 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 17:21:31 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <ctype.h>

int tokenize(t_token **token_list, char *str)
{
    size_t i;
    
    if(!str)
        return(0);
    i = 0;
    if(is_redirect(&str[i]))
        i += handle_redirect(token_list, &str[i]);
    else if(str[i] == '|')
        i += handle_pipe(token_list, &str[i]);
    else if(str[i] == '\'')
        i += handle_single_quotes(token_list, &str[i]);
    else if(str[i] == '"')
        i += handle_double_quotes(token_list, &str[i]);
    else
        i += handle_word(token_list, &str[i]);
    return(i);
}

t_token *tokenize_input(char *input)
{
    t_token *token_list = NULL;
    //size_t i;
    size_t consumed;
    
    if(!input)
        return NULL; //or '0';
    //i = 0;
    consumed = 0;
    while(*input)
    {
        while(*input && isspace((unsigned char)*input))
            input++;
        if(!*input)
            break;
        consumed = tokenize(&token_list, input);
        if(consumed == 0)
        {
            printf("Error detected:...");
            break;
        }
        input += consumed;
    }
    // print_tokens(token_list);  // Debug function - commented out
    //free_tokens(&token_list);
    return(token_list);
}
