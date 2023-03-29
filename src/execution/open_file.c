/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:56:01 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/28 15:01:54 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	open_file_util(int i, t_cmd *cmd, int *read_fd, int *write_fd)
{
	if (cmd->file[i].redirection == 1 || cmd->file[i].redirection == 2)
	{
		if (*read_fd != STDIN_FILENO)
			close(*read_fd);
		*read_fd = open(cmd->file[i].name, O_RDONLY);
		if (*read_fd < 0)
			return (error_open(cmd->file[i].name));
	}
	else
	{
		if (*write_fd != STDOUT_FILENO)
			close(*write_fd);
		if (cmd->file[i].redirection == 3)
			*write_fd = open(cmd->file[i].name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			*write_fd = open(cmd->file[i].name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*write_fd < 0)
			return (error_open(cmd->file[i].name));
	}
	return (0);
}

int	open_file(t_cmd *cmd, int *read_fd, int *write_fd)
{
	int	i;

	i = 0;
	while (cmd->file[i].redirection)
	{
		if (open_file_util(i, cmd, read_fd, write_fd))
			return (1);
		++i;
	}
	return (0);
}
