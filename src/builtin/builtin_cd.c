/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:44:28 by migo              #+#    #+#             */
/*   Updated: 2023/03/06 16:19:15 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <fcntl.h>

int	rule_cd(char *str)
{
	int		fd;
	int		i;
	char	path[4096];

	if (getcwd(path, 4096) == NULL)
		return (0);
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
	return (1);
}

void	cd_option(char *str)
{
	char	path[4096];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (getcwd(path, 4096) == NULL)
		return ;
	if (rule_cd(str) == 0)
		return ;
	if (str[0] == '/')
	{
		if (chdir(str) < 0)
			printf("cd: %s: Not a directory\n", str);
		return ;
	}
	while (path[i])
		i++;
	path[i] = '/';
	i++;
	while (str[j])
		path[i++] = str[j++];
	path[i] = str[j];
	if (chdir(path) < 0)
		printf("cd: %s: Not a directory\n", str);
}

void	builtin_cd(t_cmd *cmd, t_env *tmp)
{
	char	*str;

	if (ft_strncmp((cmd->option[0]), "cd", ft_strlen(cmd->option[0])) == 0)
	{
		if (cmd->option[1] != NULL)
		{
			cd_option(cmd->option[1]);
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
		}
	}
}