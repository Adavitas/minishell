/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:55:16 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/10/26 20:15:48 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
/*Skips SPACES outside of Quotes*/
/*Detects Quotes, Operands, Words*/
/*Builds token strings in memory*/
/*Steps:Raw Input(str)->Scan char by char -> Build linked lists->Pass to parser*/

void    tokenizer_input(char *input)
{
    t_token *token_list = NULL;
    
    size_t i = 0;
    while(input[i])
    {
        /*skip white spaces*/
        while(isspace(input[i]))
        {
            i++;
            continue;
        }
        if(is_operator(input + i))
            i += handle_operator(&token_list, input + i); /*to jump to the next cmd*/
        else if(input[i] == '\'' || input[i] == '\"')
            i += handle_quotes(&token_list, input + i);//input is pointer to the first char input
        else
            i += handle_words(&token_list, input + i);
    }
    print_tokens(token_list);
    free_tokens(token_list);
}