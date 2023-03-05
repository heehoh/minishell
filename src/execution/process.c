/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:05:24 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/05 17:27:40 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/minishell.h"
#include <fcntl.h>
#include <stdlib.h>

void	close_pipe(int *pipe, int pipe_count, int read_fd, int write_fd)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe[i] != read_fd && pipe[i] != write_fd)
			close(pipe[i]);
	}
}

void	open_file(t_cmd *cmd, int *read_fd, int *write_fd)
{
	int	i;

	i = 0;
	while (cmd->file[i].redirection)
	{
		if (cmd->file[i].redirection == 1 && cmd->file[i].redirection == 2)
		{
			close(*read_fd);
			*read_fd = open(cmd->file[i].name, O_RDONLY);
		}
		else if (cmd->file[i].redirection == 3)
		{
			close(*write_fd);
			*write_fd = open(cmd->file[i].name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (cmd->file[i].redirection == 4)
		{
			close(*write_fd);
			*write_fd = open(cmd->file[i].name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
	}
}

void	process(t_cmd *cmd, int read_fd, int write_fd, t_env *env)
{
	open_file(cmd, &read_fd, &write_fd);
	if (read_fd != 0)
		dup2(read_fd, 0);
	if (write_fd != 0)
		dup2(write_fd, 1);
	if (is_builtin(cmd->option[0]))
	{
		builtin_process();
		exit(0);
	}
	execve(cmd->option[0], cmd->option, NULL);
}
