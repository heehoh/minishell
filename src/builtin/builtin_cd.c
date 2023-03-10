/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:44:28 by migo              #+#    #+#             */
/*   Updated: 2023/03/10 10:46:20 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <fcntl.h>
#include <stdio.h>

int	rule_cd(char *str, char *path)
{
	int		fd;
	int		i;

	if (str[0] == '.' && str[1] == '.')
	{
		i = ft_strlen((path)) - 1;
		while ((path)[i] != '/')
			i--;
		(path)[i] = '\0';
		chdir(path);
		return (0);
	}
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		printf("cd: %s: No such file or directory\n", str);
		return (0);
	}
	if (ft_strlen(str) + ft_strlen(path) > 4096)
	{
		printf("path is too long");
		return (0);
	}
	return (1);
}

int	cd_option(char *str, int i, int j)
{
	char	path[4096];

	if (getcwd(path, 4096) == NULL)
		return (1);
	if (rule_cd(str, path) == 0)
		return (1);
	if (str[0] == '/')
	{
		if (chdir(str) < 0)
			printf("cd: %s: Not a directory\n", str);
		return (1);
	}
	while (path[i])
		i++;
	path[i] = '/';
	i++;
	while (str[j])
		path[i++] = str[j++];
	path[i] = str[j];
	if (chdir(path) < 0)
	{
		printf("cd: %s: Not a directory\n", str);
		return (1);
	}
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_env *tmp)
{
	char	*str;

	if (cmd->option[1] != NULL)
	{
		return (cd_option(cmd->option[1], 0, 0));
	}
	else
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->var, "HOME", 4) == 0)
				break ;
			tmp = tmp->next;
		}
		if (ft_strncmp(tmp->var, "HOME", 4) == 0)
		{
			str = ft_strdup((tmp->var + 5));
			chdir(str);
			free(str);
		}
		return (0);
	}
}

// cd 에서 $PWD $OLDPWD 를 바꾸어 주어야함