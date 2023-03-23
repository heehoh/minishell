/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:14:51 by migo              #+#    #+#             */
/*   Updated: 2023/03/23 17:01:31 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../process.h"
#include <stdio.h>

int	builtin_env(t_cmd *cmd, t_env *tmp, int write_fd)
{
	int	i;

	if (cmd->option[1] == NULL)
	{
		while (tmp)
		{
			i = 0;
			while (tmp->var[i])
			{
				if (tmp->var[i] == '=')
				{
					write(write_fd, tmp->var, ft_strlen(tmp->var));
					write(write_fd, "\n", 1);
				}
				i++;
			}
			tmp = tmp->next;
		}
		return (0);
	}
	else
	{
		write(2, "env with no options or arguments\n", 33);
		return (1);
	}
}
