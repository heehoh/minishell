/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:18:52 by migo              #+#    #+#             */
/*   Updated: 2023/03/10 14:05:40 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	not_num(char *str)
{
	write(2, "minishell: exit: ", 17);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

void	builtin_exit(t_cmd *cmd, int count)
{
	if (count == 1)
		write(1, "exit\n", 5);
	if (cmd->option[1] == NULL)
		exit(0);
	if (ft_atoll(cmd->option[1]) > 2147483647
		|| ft_atoll(cmd->option[1]) < -2147483648)
		not_num(cmd->option[1]);
	if (cmd->option[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		exit(1);
	}
	exit(ft_atoll(cmd->option[1]));
}
