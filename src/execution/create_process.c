/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:03 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/23 11:12:29 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "../process.h"

void	set_signal_ignore(void);

void	set_process(t_process *process, t_cmd *cmd, t_env *env)
{
	process->cmd = cmd;
	process->env = env;
	process->count = cmd_count(cmd);
}

void	set_pid_pipe(pid_t **pid, int **fd, int count)
{
	int	i;

	*pid = (pid_t *)malloc(sizeof(pid_t) * count);
	if (*pid == NULL)
		error_malloc();
	if (count > 1)
	{
		*fd = (int *)malloc(sizeof(int) * (2 * (count - 1)));
		if (*fd == NULL)
			error_malloc();
		i = 0;
		while (i < count - 1)
		{
			if (pipe(*fd + (2 * i)) < 0)
				error_pipe();
			++i;
		}
	}
	else
		*fd = NULL;
}

void	create_process_util(t_process *process, int *fd, int i,
	t_current *current)
{
	if (process->count == 1)
		execute_process(process, STDIN_FILENO, STDOUT_FILENO, current);
	else if (i == 0)
	{
		close_pipe(fd, process->count, STDIN_FILENO, fd[1]);
		execute_process(process, STDIN_FILENO, fd[1], current);
	}
	else if (i == process->count - 1)
	{
		close_pipe(fd, process->count, fd[2 * (i - 1)], STDOUT_FILENO);
		execute_process(process, fd[2 * (i - 1)], STDOUT_FILENO, current);
	}
	else
	{
		close_pipe(fd, process->count, fd[2 * (i - 1)], fd[2 * i + 1]);
		execute_process(process, fd[2 * (i - 1)], fd[2 * i + 1], current);
	}
}

int	create_process_loop(t_process *process, t_current *current)
{
	pid_t	*pid;
	int		*fd;
	int		i;

	set_pid_pipe(&pid, &fd, process->count);
	i = 0;
	while (i < process->count)
	{
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
		++i;
	}
	close_pipe(fd, process->count, STDIN_FILENO, STDOUT_FILENO);
	free(fd);
	return (wait_process(process->count, pid));
}

int	create_process(t_cmd *cmd, t_env *env, t_current *current)
{
	t_process	process;

	set_signal_ignore();
	here_doc_file(cmd, env);
	set_process(&process, cmd, env);
	if (process.count == 1 && cmd->option[0] != NULL
		&& is_builtin(cmd->option[0]))
		return (execute_parent_process(&process,
				STDIN_FILENO, STDOUT_FILENO, current));
	return (create_process_loop(&process, current));
}
