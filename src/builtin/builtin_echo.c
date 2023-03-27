/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:01:05 by migo              #+#    #+#             */
/*   Updated: 2023/03/27 13:59:12 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"

int	builtin_echo(t_cmd *cmd, int write_fd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (cmd->option[1] == NULL)
		return (0);
	if (ft_strncmp((cmd->option[1]), "-n", ft_strlen("-n")) == 0)
	{
		i++;
		flag = 1;
	}
	while (cmd->option[i])
	{
		write(write_fd, cmd->option[i], ft_strlen(cmd->option[i]));
		write(write_fd, " ", 1);
		i++;
	}
	if (flag == 0)
		write(write_fd, "\n", 1);
	return (0);
}
