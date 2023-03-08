/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:29:52 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/08 17:56:06 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../../libft/libft.h"

void	error_malloc(void)
{
	perror("memory allocation fail\n");
	exit(EXIT_FAILURE);
}

void	error_pipe(void)
{
	perror("pipe error\n");
	exit(EXIT_FAILURE);
}

void	error_fork(void)
{
	perror("fork error\n");
	exit(EXIT_FAILURE);
}

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
