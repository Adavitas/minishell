/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:56:43 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/10/26 21:38:43 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int ft_isspace(char c);

int ft_isalpha(char c);

int ft_isdigit(char c);

char *ft_substr(char *input, unsigned int start, int len)
{
    char *sub;
    size_t i = 0;

    if(!input)
        return NULL;
    
    sub = malloc(len + 1);
    if(!sub)
        return NULL;
    while(i < len && input[start + i])
    {
        input[i] = sub[start + i];
        i++;
    }
    sub[i] = '\0';
    return sub;
}