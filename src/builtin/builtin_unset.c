/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:19:05 by migo              #+#    #+#             */
/*   Updated: 2023/03/03 13:59:01 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

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

void	builtin_unset(t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*pre_tmp;
	int		i;

	i = 1;
	if (ft_strncmp((cmd->option[0]), "unset", ft_strlen(cmd->option[0])) == 0)
	{
		while (cmd->option[i])
		{
			tmp = g_global;
			if (strncmp(cmd->option[i], tmp->var, cp_env(tmp->var)) == 0)
			{
				g_global = tmp->next;
				free(tmp);
				break ;
			}
			while (tmp)
			{
				pre_tmp = tmp;
				tmp = tmp->next;
				if (strncmp(cmd->option[i], tmp->var, cp_env(tmp->var)) == 0)
				{
					pre_tmp->next = tmp->next;
					free(tmp);
					break ;
				}
			}
			i++;
		}
	}
}