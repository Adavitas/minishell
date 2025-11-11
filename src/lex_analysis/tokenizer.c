/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:55:16 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 22:03:45 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	tokenize(t_token **token_list, char *str)
{
    size_t	i;

    if (!str)
        return (0);
    i = 0;
    if (is_redirect(&str[i]))
        i += handle_redirect(token_list, &str[i]);
    else if (str[i] == '|')
        i += handle_pipe(token_list, &str[i]);
    else if (str[i] == '\'')
        i += handle_single_quotes(token_list, &str[i]);
    else if (str[i] == '"')
        i += handle_double_quotes(token_list, &str[i]);
    else
        i += handle_word(token_list, &str[i]);
    return (i);
}

t_token	*tokenize_input(char *input)
{
    t_token	*token_list;
    size_t	consumed;

    token_list = NULL;
    if (!input)
        return (NULL);
    consumed = 0;
    while (*input)
    {
    while (*input && ft_isspace((unsigned char)*input))
            input++;
        if (!*input)
            break;
        consumed = tokenize(&token_list, input);
        if (consumed == 0)
        {
            printf("Error detected:...\n");
            break;
        }
        input += consumed;
    }
    return (token_list);
}
