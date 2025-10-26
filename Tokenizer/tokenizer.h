/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:55:37 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/10/26 17:32:22 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// #include <readline.h> //realine; -lreadline; why ERROR?
// #include <history.h> //readline; why ERROR
#include <stdio.h> //printf;
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> //file operations;
#include <sys/wait.h> // for processors;
#include <signal.h> // for signals;
#include <sys/stat.h> //file information;
#include <dirent.h> //directory reading;
#include <string.h> //error message handling;
#include <sys/ioctl.h> //terminal operations;
#include <termios.h> //terminal attributes;
#include <termcap.h> //for temrinal control;
#include <readline/readline.h>
#include <readline/history.h>
#include <function.h>

/* Detect: WORD, QUOTES, OPERATORS, ENV VARIABLES REF...*/

typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
}   t_token_type;

typedef struct s_token
{
    char    *value;
    t_token_type    type;
    struct s_token  *next;
}   t_token;

#endif