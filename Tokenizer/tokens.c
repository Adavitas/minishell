/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:55:25 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/10/15 20:04:05 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char *extract_word(const char *line, int *i);

char *extract_quoted_word(const char *line, int *i);

char *extract_operator(const char *line, int *i);
