/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:19:53 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/10 10:58:55 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"
#include "../minishell.h"

int	builtin_pwd(t_current *current)
{
	if (current->path[0] == '\0')
	{
		write(2, "pwd: error retrieving current directory:", 40);
		if (getcwd(current->path, 4096) == NULL)
		{
			write(2, "getcwd: cannot access parent directories", 41);
			write(2, ": No such file or directory\n", 28);
			return (1);
		}
		write(1, current->path, ft_strlen(current->path));
	}
	else
		write(1, current->path, ft_strlen(current->path));
	write(1, "\n", 1);
	return (0);
}

