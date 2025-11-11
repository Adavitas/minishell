/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:44:05 by adavitas          #+#    #+#             */
/*   Updated: 2025/11/11 18:44:09 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_in(t_redir *redir)
{
	int	fd;

	fd = open_infile(redir->filename);
	if (fd < 0)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redir_out(t_redir *redir, int append)
{
	int	fd;

	fd = open_outfile(redir->filename, append);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_heredoc_redir(t_redir *redir)
{
	int	fd;

	fd = handle_heredoc(redir->filename);
	if (fd < 0)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	setup_redirections(t_redir *redirs)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (current->type == NODE_REDIR_IN)
			handle_redir_in(current);
		else if (current->type == NODE_REDIR_OUT)
			handle_redir_out(current, 0);
		else if (current->type == NODE_APPEND)
			handle_redir_out(current, 1);
		else if (current->type == NODE_HEREDOC)
			handle_heredoc_redir(current);
		current = current->next;
	}
}
