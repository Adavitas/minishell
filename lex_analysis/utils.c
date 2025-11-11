/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:56:43 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 16:23:35 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int ft_strcmp(const char *s1, const char *s2)
{
    if(!s1 || !s2)
        return(s1 == s2 ? 0 : (s1 ? 1 : -1)); //handle NULLs safely;
    int i = 0;
    while(s1[i] && s1[i] == s2[i])
        i++;
    return((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_substr(char *input, unsigned int start, size_t len)
{
    char *sub;
    size_t i = 0;

    if(!input)
        return NULL;
    if (len < 0)
        return (NULL);

    sub = malloc((size_t)len + 1);
    if(!sub)
        return NULL;
    while(i < (size_t)len && input[start + i])
    {
        sub[i] = input[start + i];
        i++;
    }
    sub[i] = '\0';
    return sub;
}

int ft_strlen(char *str)
{
    int i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char *ft_strdup(char *str)
{
    if(!str)
        return NULL;
    char *new_str;
    int len;
    int i;

    len = ft_strlen(str);
    new_str = malloc(sizeof(char) * (len + 1));
    if(!new_str)
        return (NULL);
    i = 0;
    while(i < len)
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return(new_str);
}