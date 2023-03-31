/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:02:46 by migo              #+#    #+#             */
/*   Updated: 2023/03/31 16:54:13 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../process.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

int	builtin_process(t_process *process, t_current *current, int write_fd)
{
	char	*command;

	command = process->cmd->option[0];
	if (ft_strncmp(command, "cd", 3) == 0)
		return (builtin_cd(process->cmd, process->env, current));
	if (ft_strncmp(command, "echo", 5) == 0)
		return (builtin_echo(process->cmd, write_fd));
	if (ft_strncmp(command, "env", 4) == 0)
		return (builtin_env(process->cmd, process->env, write_fd));
	if (ft_strncmp(command, "export", 7) == 0)
		return (builtin_export(process, 0, 0, write_fd));
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (builtin_pwd(current, write_fd));
	if (ft_strncmp(command, "unset", 6) == 0)
		return (builtin_unset(process, 0, 0, current));
	if (ft_strncmp(command, "exit", 5) == 0)
		builtin_exit(process->cmd, process->count, process->env, current);
	return (1);
}
