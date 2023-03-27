/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:03:32 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/27 11:32:32 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../../libft/libft.h"

void	error_open(char *name)
{
	write(2, "minishell: ", 11);
	perror(name);
	exit(EXIT_FAILURE);
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
