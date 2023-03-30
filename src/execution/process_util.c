/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:53:21 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/30 11:42:56 by hujeong          ###   ########.fr       */
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

	i = 0;
	if (process_count == 2)
	{
		while (i < 2)
		{
			if (fd[i] != read_fd && fd[i] != write_fd)
				close(fd[i]);
			++i;
		}
		return ;
	}
	while (i < 4)
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
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == 3)
			write(1, "Quit: 3\n", 8);
		else
			write(1, "\n", 1);
		return (status + 128);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
