/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:55:50 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/10/26 20:16:26 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *tmp_dest;
    unsigned char *tmp_src;
    int i;

    if(dest == (void *)0 && src == (void *)0)
        return ;

    tmp_dest = (unsigned char *)dest;
    tmp_src = (unsigned char *)src;

    i = 0;
    while(n > 0)
    {
        tmp_dest[i] = tmp_src[i];
        i++;
        n--;
    }
    return (dest);
}

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;
    size_t copy_size;

    if(new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if(!new_ptr)
        return NULL;
    
    if(ptr)
    {
        if(old_size < new_size)
            copy_size = old_size;
        else
            copy_size = new_size;
        ft_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }
    return (new_ptr);
}

void free_tokens(t_token **head)
{
    t_token *tmp;

    if(!head || !*head)
        return ;

    while(head && (*head)->next != NULL)
    {
        tmp = head;
        free(tmp);
        head = (*head)->next;
    }
}
