/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacent_concan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:11:43 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 16:24:22 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int  is_delim_char(char c)
{
    return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

static void append_to_token_value(t_token *token, const char *add)
{
    size_t a = 0;
    size_t b = 0;
    char *newv;

    if (!token || !add)
        return;
    a = (size_t)ft_strlen(token->value);
    b = (size_t)ft_strlen((char *)add);
    newv = malloc(a + b + 1);
    if (!newv)
        return;
    if (token->value)
        memcpy(newv, token->value, a);
    if (b > 0)
        memcpy(newv + a, add, b);
    newv[a + b] = '\0';
    if (token->value)
        free(token->value);
    token->value = newv;
}

/* Collect adjacent parts after a quoted token: unquoted word parts or further
   quoted parts should be concatenated into the same token value until a
   delimiter (space or operator) is reached. Returns number of characters
   consumed beyond `pos` (pos is index of the first char to examine). */
int  collect_adjacent_parts(t_token *token, char *input, int pos)
{
    int start = pos;
    int j;
    char *part;

    while (input[pos] && !is_delim_char(input[pos]))
    {
        if (input[pos] == '\'')
        {
            j = pos + 1;
            while (input[j] && input[j] != '\'')
                j++;
            if (!input[j])
                break; /* unmatched quote -> stop concatenation; caller handles error */
            part = ft_substr(input, pos + 1, j - pos - 1);
            if (part)
            {
                append_to_token_value(token, part);
                free(part);
            }
            pos = j + 1;
        }
        else if (input[pos] == '"')
        {
            j = pos + 1;
            while (input[j] && input[j] != '"')
                j++;
            if (!input[j])
                break;
            part = ft_substr(input, pos + 1, j - pos - 1);
            if (part)
            {
                append_to_token_value(token, part);
                free(part);
            }
            pos = j + 1;
        }
        else
        {
            j = pos;
            while (input[j] && input[j] != '\'' && input[j] != '"' && !is_delim_char(input[j]))
                j++;
            if (j == pos)
                break;
            part = ft_substr(input, pos, j - pos);
            if (part)
            {
                append_to_token_value(token, part);
                free(part);
            }
            pos = j;
        }
    }
    return (pos - start);
}
