/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:03 by hujeong           #+#    #+#             */
/*   Updated: 2023/04/19 19:44:33 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "../process.h"

void	set_signal_ignore(void);
void	set_signal(void);

void	set_process(t_process *process, t_cmd *cmd, t_env *env)
{
	process->cmd = cmd;
	process->env = env;
	process->count = cmd_count(cmd);
}

void	open_pipe(int *fd, int i)
{
	if (i % 2 == 0)
	{
		if (i != 0)
		{
			close(fd[0]);
			close(fd[1]);
		}
		if (pipe(fd) == -1)
			error_pipe();
	}
	else
	{
		if (i != 1)
		{
			close(fd[2]);
			close(fd[3]);
		}
		if (pipe(fd + 2) == -1)
			error_pipe();
	}
}

void	create_process_util(t_process *process, int *fd, int i,
														t_current *current)
{
	int	read_fd;
	int	write_fd;

	if (i % 2 == 0)
	{
		read_fd = fd[2];
		write_fd = fd[1];
	}
	else
	{
		read_fd = fd[0];
		write_fd = fd[3];
	}
	if (i == 0)
		read_fd = STDIN_FILENO;
	if (i == process->count - 1)
		write_fd = STDOUT_FILENO;
	close_pipe(fd, process->count, read_fd, write_fd);
	execute_process(process, read_fd, write_fd, current);
}

int	create_process_loop(t_process *process, t_current *current)
{
	pid_t	*pid;
	int		fd[4];
	int		i;

	pid = (pid_t *)malloc(sizeof(pid_t) * process->count);
	if (pid == NULL)
		error_malloc();
	i = -1;
	while (++i < process->count)
	{
		if (i != process->count - 1)
			open_pipe(fd, i);
		pid[i] = fork();
		if (pid[i] < 0)
		{
			if (i > 0)
				wait_process(i, pid);
			error_fork();
		}
		else if (pid[i] == 0)
			create_process_util(process, fd, i, current);
		process->cmd = process->cmd->next;
	}
	close_pipe(fd, process->count, STDIN_FILENO, STDOUT_FILENO);
	return (wait_process(process->count, pid));
}

int	create_process(t_cmd *cmd, t_env *env, t_current *current)
{
	t_process	process;

	signal(SIGINT, SIG_IGN);
	if (here_doc_fork(cmd, env))
	{
		set_signal();
		return (1);
	}
	set_process(&process, cmd, env);
	if (process.count == 1 && cmd->option[0] != NULL
		&& is_builtin(cmd->option[0]))
		return (execute_parent_process(&process,
				STDIN_FILENO, STDOUT_FILENO, current));
	return (create_process_loop(&process, current));
}
