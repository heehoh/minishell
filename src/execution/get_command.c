/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:39:41 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/06 20:50:41 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../process.h"

char	**get_path(t_env *env)
{

}

char	*cmd_with_path(char *cmd, char **path)
{

}

char	*get_command(char *cmd, t_env *env)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			if (access(cmd, F_OK) == -1 || access(cmd, X_OK) == -1)
				error_access();
			else
				return (cmd);
		}
		++i;
	}
	return (cmd_with_path(cmd, get_path(env)));
}
