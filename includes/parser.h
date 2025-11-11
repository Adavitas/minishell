/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:32:45 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/11/11 16:20:35 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

typedef enum e_token_type
{
    WORD, /*Word is anything other than command symbols*/
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
    UNKNOWN,
}   t_tokentype;

typedef enum e_quoted_type
{
    NO_QUOTE, /*normal unquoted string*/
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
}   t_quote_type;

typedef struct s_quote_token
{
    char    *value; /*the content inside the quotes*/
    t_quote_type    qtype; /*single or double*/
    struct  s_quote_token *next; /*for linked list if needed*/
}   t_quote_token;

typedef struct s_token
{
    char    *value; /*original token string*/
    t_tokentype    type; /*WORD, PIPE, REDIR_IN, OUT*/
    t_quote_token   *quote; /*NULL if unquoted*/
    struct s_token  *next;
}   t_token;

typedef enum e_node_type
{
    NODE_COMMAND,
    NODE_PIPE,
    NODE_REDIR_IN,
    NODE_REDIR_OUT,
    NODE_APPEND,
    NODE_HEREDOC,
    NODE_INVALID,
} t_node_type;

typedef struct s_redir
{
    t_node_type type;
    char *filename;
    struct s_redir *next;
}   t_redir;

typedef struct s_ast
{
    t_node_type type;
    char **argv;        // command + args
    t_redir *redirections;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;

char **store_avs(t_token **tokens);
t_ast *create_ast_node(t_node_type type);
t_ast *create_command_node(t_token **tokens);
t_redir *create_redir(t_node_type type, t_token **tokens);
t_ast *create_pipe_node(t_node_type type, t_ast *left, t_ast *right);
int is_redirection(t_tokentype type);
t_node_type detect_redir_type(t_token *tokens);
void append_redir(t_redir **redir_list, t_redir *new_redir);
t_ast *parse_command(t_token **tokens);
t_ast *parse_pipeline(t_token **tokens);
t_ast *syntax_analysis(t_token **token_list);
int syntax_check(t_token **tokens);

#endif