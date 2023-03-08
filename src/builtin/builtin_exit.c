/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:18:52 by migo              #+#    #+#             */
/*   Updated: 2023/03/08 14:08:34 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	builtin_exit(t_cmd *cmd)
{
	printf("exit");
	if (cmd->option[1] != NULL)
		exit(0);
	if (ft_atoll(cmd->option[1]) > 2147483647
		|| ft_atoll(cmd->option[1]) < -2147483648)
	{
		printf("exit: %s: numeric argument required\n", cmd->option[1]);
		exit(1);
	}
	if (cmd->option[2] != NULL)
	{
		printf("exit: too many arguments\n");
		exit(1);
	}
	exit(ft_atoll(cmd->option[1]));
}
