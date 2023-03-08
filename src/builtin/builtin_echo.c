/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:01:05 by migo              #+#    #+#             */
/*   Updated: 2023/03/08 14:07:06 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (cmd->option[1] == NULL)
		return (0);
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
	return (0);
}
