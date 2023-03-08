/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:02:46 by migo              #+#    #+#             */
/*   Updated: 2023/03/08 16:16:08 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"

#include <stdio.h>

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(command, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen("env")) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen("unset")) == 0)
		return (1);
	if (ft_strncmp(command, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

int	builtin_process(t_cmd *cmd, t_env *env)
{
	if (ft_strncmp((cmd->option[0]), "cd", ft_strlen("cd")) == 0)
		return (builtin_cd(cmd, env));
	if (ft_strncmp((cmd->option[0]), "echo", ft_strlen("echo")) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp((cmd->option[0]), "env", ft_strlen("env")) == 0)
		return (builtin_env(cmd, env));
	if (ft_strncmp((cmd->option[0]), "export", ft_strlen("export")) == 0)
		return (builtin_export(cmd, env));
	if (ft_strncmp((cmd->option[0]), "pwd", ft_strlen("pwd")) == 0)
		return (builtin_pwd());
	if (ft_strncmp((cmd->option[0]), "unset", ft_strlen("unset")) == 0)
		return (builtin_unset(cmd, env, 0));
	if (ft_strncmp((cmd->option[0]), "exit", ft_strlen("exit")) == 0)
		builtin_exit(cmd);
	return (0);
}
