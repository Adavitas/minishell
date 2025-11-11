/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:17:58 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 20:12:35 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_quote_token	*store_quote(char *str, t_quote_type qtype)
{
	t_quote_token	*q;
	
	q = malloc(sizeof(t_quote_token));
	if (!q)
		return NULL;
	q->value = str;
	q->qtype = qtype;
	q->next = NULL;
	return(q);
}

t_token	*make_main_token_single(char *single_quote)
{
	t_token *token;
	t_quote_token *quote_str;
	
	token = malloc(sizeof(t_token));
	if(!token)
        return NULL;
    quote_str = store_quote(single_quote, SINGLE_QUOTE);
    if(!quote_str)
    {
        free(token);
        return NULL;
    }
    token->value = ft_strdup(single_quote); //not to doubele free;
    token->type = TOKEN_WORD;
    token->quote = quote_str; //original str, separate pointer from token->value;
    token->next = NULL;
    return(token);
}

int handle_single_quotes(t_token **token_list, char *input)
{
    int i;
    char *single_quote;
    t_token *token;

    i = 1;
    if(input[0] == '\'')
        while(input[i] && input[i] != '\'')
            i++;
    if(!input[i]) //unmatched quote - need to create msg for uq in tokenizer;
        return(0);
    single_quote = ft_substr(input, 1, i - 1); //i = ';
    if(!single_quote)
        return(0);
    token = make_main_token_single(single_quote);
    if(!token)
    {
        free(single_quote);
        return(0); //control return;
    }
    /* collect adjacent parts (e.g. "a b"c  -> token value becomes: a bc) */
    add_token_back(token_list, token);
    {
        int extra = collect_adjacent_parts(token, input, i + 1);
        return (i + 1 + extra);
    }
}

t_token *make_main_token_double(char *double_quote)
{
    t_token *token;
    t_quote_token *quote_str;
    
    token = malloc(sizeof(t_token));
    if(!token)
        return(NULL);
    quote_str = store_quote(double_quote, DOUBLE_QUOTE);
    if(!quote_str)
    {
        free(token);
        return NULL;
    }
    token->value = ft_strdup(double_quote);
    token->type = TOKEN_WORD;
    token->quote = quote_str;
    token->next = NULL;
    return(token);
}

int handle_double_quotes(t_token **token_list, char *input)
{
    int i;
    t_token *token;
    char *double_quote;
    
    i = 1;
    if(input[0] == '\"')
        while(input[i] && input[i] != '\"')
            i++;
    if(!input[i])
        return(0); //unmatched quote case - need to make msg for debug;
    double_quote = ft_substr(input, 1, i - 1);
    if(!double_quote)
        return(0);
    token = make_main_token_double(double_quote);
    if(!token)
    {
        free(double_quote);
        return(0);
    }
    /* collect adjacent parts after closing double quote */
    add_token_back(token_list, token);
    {
        int extra = collect_adjacent_parts(token, input, i + 1);
        return (i + 1 + extra);
    }
}

int handle_pipe(t_token **token_list, char *input)
{
    int len = 0;
    t_token *token;
    char *pipe_str;
    
    if(input[0] == '|')
        len = 1;
    pipe_str = ft_substr(input, 0, len); //mem allocated in ft;
    if(!pipe_str)
        return(0);
    token = create_token(pipe_str, TOKEN_PIPE); //t_token token has memory ownership;
    if(!token)
    {
        free(pipe_str);
        return(0);
    }
    add_token_back(token_list, token);
    free(pipe_str);
    return (len);
}

int handle_redirect(t_token **token_list, char *input)
{
    int len;
    t_token_type type;
    char *redir;
    t_token *token;
    
    if((input[0] == '>' && input[1] == '>') ||
        (input[0] == '<' && input[1] == '<'))
        len = 2;
    else
        len = 1;
    redir = ft_substr(input, 0, len);
    if(!redir)
        return(0);
    type = get_op_type(redir);
    token = create_token(redir, type);
    if(!token)
    {
        free(redir);
        return(0);
    }
    add_token_back(token_list, token);
    free(redir);
    return (len);
}

int handle_word(t_token **token_list, char *input)
{
    int i;
    char *word_str;
    t_token *token;

    i = 0;
    while(input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '<' 
        && input[i] != '>' && input[i] != '\'' && input[i] != '\"')
        i++;
    word_str = ft_substr(input, 0, i);
    if(!word_str)
        return(0);
    token = create_token(word_str, TOKEN_WORD);
    if(!token)
    {
        free(word_str);
        return(0);
    }
    add_token_back(token_list, token);
    free(word_str);
    return(i);
}
