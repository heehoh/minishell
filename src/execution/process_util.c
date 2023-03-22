/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:53:21 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/22 16:29:05 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	set_signal(void);

int	cmd_count(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		cmd = cmd->next;
		++count;
	}
	return (count);
}

void	close_pipe(int *fd, int process_count, int read_fd, int write_fd)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = (process_count - 1) * 2;
	while (i < pipe_count)
	{
		if (fd[i] != read_fd && fd[i] != write_fd)
			close(fd[i]);
		++i;
	}
}

int	wait_process(int count, pid_t *pid)
{
	int	status;
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(pid[i], &status, 0);
		++i;
	}
	set_signal();
	free(pid);
	if ((status & 0177) != 0177 && (status & 0177) != 0)
	{
		status = status & 0177;
		if (status == 3)
			write(1, "Quit: 3\n", 8);
		else
			write(1, "\n", 1);
		return (status + 128);
	}
	else if ((status & 0177) == 0)
		status = (status >> 8) & 0xff;
	return (status);
}
