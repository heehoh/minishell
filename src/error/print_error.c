/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:29:52 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/07 12:51:56 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	error_malloc(void)
{
	perror("memory allocation fail\n");
	exit(1);
}

void	error_pipe(void)
{
	perror("pipe error\n");
	exit(1);
}

void	error_fork(void)
{
	perror("fork error\n");
	exit(1);
}

void	error_open(char *name)
{
	write(2, "minishell: ", 11);
	perror(name);
}

void	error_access(char *cmd)
{
	write(2, "minishell: ", 11);
	perror(cmd);
}
