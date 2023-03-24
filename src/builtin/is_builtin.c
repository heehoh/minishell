/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:02:46 by migo              #+#    #+#             */
/*   Updated: 2023/03/24 18:10:13 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../process.h"
#include "../minishell.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

int	builtin_process(t_process *process, t_current *current, int write_fd)
{
	char	*cmd;

	cmd = process->cmd->option[0];
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (builtin_cd(process->cmd, process->env, current));
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (builtin_echo(process->cmd, write_fd));
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (builtin_env(process->cmd, process->env, write_fd));
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (builtin_export(process, 0, 0, write_fd));
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (builtin_pwd(current, write_fd));
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (builtin_unset(process, 0, 0, current));
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		builtin_exit(process->cmd, process->count, process->env, current);
	return (1);
}
