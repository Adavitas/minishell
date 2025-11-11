/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:55:37 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 17:21:30 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

/* Token types - Detect: WORD, QUOTES, OPERATORS, ENV VARIABLES REF */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_UNKNOWN,
}	t_token_type;

/* Quote types */
typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote_type;

/* Quote token structure - stores content inside quotes */
typedef struct s_quote_token
{
	char					*value;
	t_quote_type			qtype;
	struct s_quote_token	*next;
}	t_quote_token;

/* Token structure */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_token	*quote;
	struct s_token	*next;
}	t_token;

/* Tokenizer function prototypes */
t_quote_token	*store_quote(char *str, t_quote_type qtype);
t_token			*make_main_token_single(char *single_quote);
int				handle_single_quotes(t_token **token_list, char *input);
t_token			*make_main_token_double(char *double_quote);
int				handle_double_quotes(t_token **token_list, char *input);
int				handle_pipe(t_token **token_list, char *input);
int				handle_redirect(t_token **token_list, char *input);
int				handle_word(t_token **token_list, char *input);
void			print_tokens(t_token *list);
t_token			*create_token(char *value, t_token_type type);
void			add_token_back(t_token **token_list, t_token *new_node);
void			free_tokens(t_token **head);
int				tokenize(t_token **token_list, char *str);
t_token			*tokenize_input(char *input);
int				is_redirect(const char *str);
t_token_type	get_op_type(char *token);
int				collect_adjacent_parts(t_token *token, char *input, int pos);

#endif