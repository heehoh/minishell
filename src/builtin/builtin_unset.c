/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:19:05 by migo              #+#    #+#             */
/*   Updated: 2023/03/09 13:18:57 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int	cp_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i - 1);
}

int	builtin_unset(t_cmd *cmd, t_env *env, int i)
{
	t_env	*tmp;
	t_env	*pre_tmp;

	if (ft_isalpha(cmd->option[1][0]) == 0)
	{
		printf("export: \'%s\': not a valid identifier\n", cmd->option[1]);
		return (1);
	}
	while (cmd->option[++i])
	{
		tmp = env;
		if (ft_strncmp(cmd->option[i], tmp->var, cp_env(tmp->var)) == 0)
		{
			env = tmp->next;
			free(tmp);
		}
		while (tmp)
		{
			pre_tmp = tmp;
			tmp = tmp->next;
			if (ft_strncmp(cmd->option[i], tmp->var, cp_env(tmp->var)) == 0)
			{
				pre_tmp->next = tmp->next;
				free(tmp);
				break ;
			}
		}
	}
	return (0);
}
