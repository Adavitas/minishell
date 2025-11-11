/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MAIN_testing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:46:00 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/10/26 16:24:40 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int main(int ac, char **av)
{
    char *input;
    t_token *tokens;
    
    while(1)
    {
        input = readline("lexer: ");
        if(!input) //Ctrl+D
            break;
        if(*input)
            add_history(input);
        
        tokens = tokenizer_input(input);
        
        printf("\nTokens:\n");
        print_tokens(tokens);
        printf("\n");
        
        free_tokens(tokens);
        free(input);
    }
    return(0);
}
