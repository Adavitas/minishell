/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:18:07 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/10/26 21:44:13 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

t_token *create_token(char *value, t_token_type type)
{
    t_token *new_node;

    new_node = malloc(sizeof(t_token));
    if(!new_node)
        return (NULL);
        
    new_node->value = strdup(value); //ft_strdup!!!
    if(!new_node->value)
    {
        free(new_node);
        return (NULL);
    }

    new_node->type = type;
    new_node->next = NULL;
    
    return new_node;
}

void add_token(t_token **head, t_tokentype type, char *value)
{
    t_token *new_node;
    t_token *tmp;
    
    new_node = malloc(sizeof(t_token));
    if(!new_node)
        return;
    
    new_node->value = ft_strdup(value);
    new_node->type = type;
    new_node->next = NULL;
    
    if(!*head)
    {
        *head = new_node;
        return;
    }
    tmp = *head;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void print_tokens(t_token *list)
{
    while(list)
    {
        printf("[%s] (type: %d)\n", list->value, list->type);
        list = list->next;
    }
}