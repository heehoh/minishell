/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:29:52 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/30 11:49:34 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	error_malloc(void)
{
	perror("memory allocation fail");
	exit(EXIT_FAILURE);
}

void	error_pipe(void)
{
	perror("pipe error");
	exit(EXIT_FAILURE);
}

void	error_fork(void)
{
	perror("fork error");
	exit(EXIT_FAILURE);
}
