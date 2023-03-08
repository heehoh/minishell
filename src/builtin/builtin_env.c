/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:14:51 by migo              #+#    #+#             */
/*   Updated: 2023/03/08 14:07:28 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int	builtin_env(t_cmd *cmd, t_env *tmp)
{
	int	i;

	if (cmd->option[1] == NULL)
	{
		i = 0;
		while (tmp)
		{
			while (tmp->var[i])
			{
				if (tmp->var[i] == '=')
					break ;
				i++;
			}
			if (tmp->var[i] != '=')
				printf("%s\n", tmp->var);
			tmp = tmp->next;
		}
		return (0);
	}
	else
	{
		printf("env with no options or arguments");
		return (1);
	}
}