/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:26:44 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/26 17:41:17 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"
#include "../minishell.h"

#define PATH_MAX 4096

void	builtin_pwd(void)
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
}

void	builtin_cd(t_cmd *cmd)
{
	if (chdir(cmd->option[1]))
		perror("cd");
}
