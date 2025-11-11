# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/11 00:00:00 by zzhyrgal          #+#    #+#              #
#    Updated: 2025/11/11 22:00:42 by zzhyrgal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes
LIBS = -lreadline

# Source files
SRCS = main.c \
	   src/lex_analysis/tokenizer.c \
	   src/lex_analysis/tokens_types.c \
	   src/lex_analysis/handle_functions.c \
	   src/lex_analysis/manage_lists.c \
	   src/lex_analysis/adjacent_concan.c \
	   src/syntax_analysis/syntax_check.c \
	   src/syntax_analysis/syntax_analysis.c \
	   src/syntax_analysis/parsers.c \
	   src/syntax_analysis/ast_nodes.c \
	   src/executor/execute_cmd.c \
	   src/executor/execute_utils.c \
	   src/executor/path.c \
	   src/executor/redirections.c \
	   src/executor/redir_files.c \
	   src/executor/heredoc.c \
	   src/executor/ast_executor.c \
	   src/executor/ast_pipe.c \
	   src/executor/ast_builtin.c \
	   src/executor/ast_helpers.c \
	   src/builtins/builtin_utils.c \
	   src/builtins/builtin_echo.c \
	   src/builtins/builtin_cd.c \
	   src/builtins/builtin_pwd.c \
	   src/builtins/builtin_export.c \
	   src/builtins/builtin_env.c \
	   src/builtins/builtin_exit.c \
	   src/env/env_init.c \
	   src/env/env_utils.c \
	   src/utils/utils.c \
	   src/utils/signals.c

# Libft sources
LIBFT_SRCS = libft/ft_atoi.c \
			 libft/ft_putstr_fd.c \
			 libft/ft_split.c \
			 libft/ft_strchr.c \
			 libft/ft_strcmp.c \
			 libft/ft_strdup.c \
			 libft/ft_strjoin.c \
			 libft/ft_strlcpy.c \
			 libft/ft_strlen.c \
			 libft/ft_strnstr.c \
			 libft/ft_substr.c \
			 libft/ft_memcpy.c \
			 libft/get_next_line.c

# Object files
OBJS = $(SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(LIBFT_OBJS)
	@echo "$(RED)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)✓ $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
