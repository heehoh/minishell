/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:51:42 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/30 11:51:42 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../process.h"
#include <fcntl.h>
#include <stdlib.h>

void	set_terminal_print_on(void);
void	set_signal(void);

void	ft_dup(int fd, int in_out)
{
	dup2(fd, in_out);
	close(fd);
}

int	execute_parent_process(t_process *process,
	int read_fd, int write_fd, t_current *current)
{
	int	status;

	set_signal();
	if (open_file(process->cmd, &read_fd, &write_fd))
	{
		if (read_fd != STDIN_FILENO)
			close(read_fd);
		if (write_fd != STDOUT_FILENO)
			close(write_fd);
		return (1);
	}
	status = builtin_process(process, current, write_fd);
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

	if (open_file(process->cmd, &read_fd, &write_fd))
		exit(1);
	if (read_fd != STDIN_FILENO)
		ft_dup(read_fd, STDIN_FILENO);
	if (write_fd != STDOUT_FILENO)
		ft_dup(write_fd, STDOUT_FILENO);
	if (process->cmd->option[0] == NULL)
		exit(0);
	if (is_builtin(process->cmd->option[0]))
		exit(builtin_process(process, current, 1));
	command = get_command(process->cmd->option[0], process->env);
	env = get_env_array(process->env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_terminal_print_on();
	if (execve(command, process->cmd->option, env) == -1)
		error_execve(process->cmd->option[0]);
}
