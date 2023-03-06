/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:14:51 by migo              #+#    #+#             */
/*   Updated: 2023/03/06 16:28:41 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	builtin_env(t_cmd *cmd, t_env *tmp)
{
	if (ft_strncmp((cmd->option[0]), "env", ft_strlen(cmd->option[0])) == 0)
	{
		if (cmd->option[1] == NULL)
		{
			while (tmp)
			{
				printf("%s\n", tmp->var);
				tmp = tmp->next;
			}
		}
	}
}