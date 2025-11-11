/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacent_concan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:11:43 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 21:52:47 by zzhyrgal         ###   ########.fr       */
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
        ft_memcpy(newv, token->value, a);
    if (b > 0)
        ft_memcpy(newv + a, add, b);
    newv[a + b] = '\0';
    if (token->value)
        free(token->value);
    token->value = newv;
}

static int	collect_single_quoted_part(t_token *token, char *input, int pos)
{
    int		j;
    char	*part;

    j = pos + 1;
    while (input[j] && input[j] != '\'')
        j++;
    if (!input[j])
        return (-1);
    part = ft_substr(input, pos + 1, j - pos - 1);
    if (part)
    {
        append_to_token_value(token, part);
        free(part);
    }
    return (j + 1);
}

static int	collect_double_quoted_part(t_token *token, char *input, int pos)
{
    int		j;
    char	*part;

    j = pos + 1;
    while (input[j] && input[j] != '"')
        j++;
    if (!input[j])
        return (-1);
    part = ft_substr(input, pos + 1, j - pos - 1);
    if (part)
    {
        append_to_token_value(token, part);
        free(part);
    }
    return (j + 1);
}

static int	collect_unquoted_part(t_token *token, char *input, int pos)
{
    int		j;
    char	*part;

    j = pos;
    while (input[j] && input[j] != '\'' && input[j] != '"' &&
        !is_delim_char(input[j]))
        j++;
    if (j == pos)
        return (pos);
    part = ft_substr(input, pos, j - pos);
    if (part)
    {
        append_to_token_value(token, part);
        free(part);
    }
    return (j);
}

int	collect_adjacent_parts(t_token *token, char *input, int pos)
{
    int	start;
    int	new_pos;

    start = pos;
    while (input[pos] && !is_delim_char(input[pos]))
    {
        if (input[pos] == '\'')
        {
            new_pos = collect_single_quoted_part(token, input, pos);
            if (new_pos == -1)
                break ;
            pos = new_pos;
        }
        else if (input[pos] == '"')
        {
            new_pos = collect_double_quoted_part(token, input, pos);
            if (new_pos == -1)
                break ;
            pos = new_pos;
        }
        else
        {
            new_pos = collect_unquoted_part(token, input, pos);
            if (new_pos == pos)
                break ;
            pos = new_pos;
        }
    }
    return (pos - start);
}
