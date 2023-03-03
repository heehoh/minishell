/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:01:05 by migo              #+#    #+#             */
/*   Updated: 2023/03/03 14:25:05 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_strncmp((cmd->option[0]), "echo", ft_strlen(cmd->option[0])) == 0)
	{
		if (cmd->option[1] == NULL)
			return ;
		if (ft_strncmp((cmd->option[1]), "-n", ft_strlen(cmd->option[0])) == 0)
		{
			i++;
			flag = 1;
		}
		while (cmd->option[i])
		{
			printf("%s", cmd->option[i]);
			i++;
		}
		if (flag == 0)
			printf("\n");
	}
}
