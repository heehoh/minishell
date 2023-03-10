/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:51:42 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/10 11:03:56 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../process.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	open_file_util(int i, t_cmd *cmd, int *read_fd, int *write_fd)
{
	if (cmd->file[i].redirection == 1 || cmd->file[i].redirection == 2)
	{
		if (*read_fd != STDIN_FILENO)
			close(*read_fd);
		*read_fd = open(cmd->file[i].name, O_RDONLY);
		if (*read_fd < 0)
			error_open(cmd->file[i].name);
	}
	else if (cmd->file[i].redirection == 3 || cmd->file[i].redirection == 4)
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
			error_open(cmd->file[i].name);
	}
}

void	open_file(t_cmd *cmd, int *read_fd, int *write_fd)
{
	int	i;

	i = 0;
	while (cmd->file[i].redirection)
	{
		open_file_util(i, cmd, read_fd, write_fd);
		++i;
	}
}

int	execute_parent_process(t_process *process,
	int read_fd, int write_fd, t_current *current)
{
	int	status;

	open_file(process->cmd, &read_fd, &write_fd);
	status = builtin_process(process->cmd, process->env,
			process->count, current);
	if (read_fd != STDIN_FILENO)
		close(read_fd);
	if (write_fd != STDOUT_FILENO)
		close(write_fd);
	return (status);
}

void	execute_process(t_process *process,
	int read_fd, int write_fd, t_current *current)
{
	char	*command;
	char	**env;

	open_file(process->cmd, &read_fd, &write_fd);
	if (read_fd != 0)
	{
		dup2(read_fd, 0);
		close(read_fd);
	}
	if (write_fd != 1)
	{
		dup2(write_fd, 1);
		close(write_fd);
	}
	if (process->cmd->option[0] == NULL)
		exit(0);
	if (is_builtin(process->cmd->option[0]))
		exit(builtin_process(process->cmd, process->env,
				process->count, current));
	command = get_command(process->cmd->option[0], process->env);
	env = get_env_array(process->env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(command, process->cmd->option, env);
}
