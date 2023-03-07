/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:19:53 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/07 20:20:22 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"

#define PATH_MAX 4096

int	builtin_pwd(void)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * PATH_MAX);
	if (path == NULL)
	{
		perror("pwd error");
		exit(1);
	}
	if (getcwd(path, PATH_MAX))
	{
		write(STDOUT_FILENO, path, ft_strlen(path));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
		perror("pwd error");
	free(path);
	return (0);
}
