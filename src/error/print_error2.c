/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:03:32 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/30 11:50:16 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"

int	error_open(char *name)
{
	write(2, "minishell: ", 11);
	perror(name);
	return (1);
}

void	error_access(char *cmd)
{
	write(2, "minishell: ", 11);
	perror(cmd);
	exit(127);
}

void	error_cmd_not_found(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit (127);
}

void	error_execve(char *cmd)
{
	write(2, "minishell: ", 11);
	perror(cmd);
	exit(126);
}
