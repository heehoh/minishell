/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:44:28 by migo              #+#    #+#             */
/*   Updated: 2023/03/08 13:34:05 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <fcntl.h>

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

int	check_dir(char *path, char *str)
{
	char	OLDPWD[4096];
	char	*pwd;

	if (getcwd(OLDPWD, 4096) == NULL)
		return (1);
	if (chdir(str) < 0)
	{
		printf("cd: %s: Not a directory\n", str);
		return (1);
	}
	else
	{
		make_OLDPWD(env);
		pwd = ft_strjoin("PWD=", path);
		rule_env(pwd, env);
		free (pwd);
		pwd = ft_strjoin("OLDPWD=", OLDPWD);
		rule_env(pwd, env);
		free (pwd);
		return (0);
	}
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
		return (check_dir(str, str));
	}
	while (path[i])
		i++;
	path[i++] = '/';
	while (str[j])
		path[i++] = str[j++];
	path[i] = str[j];
	if (chdir(path) < 0)
	{
		check_dir(path, str);
	}
	return (0);
}

void	make_OLDPWD(t_env *env)
{
	static int i;
	t_env	*OLDPWD;

	if (i = 0)
	{
		while (env)
			env = env->next;
		OLDPWD = malloc(sizeof(t_env));
		if (OLDPWD == 0)
			return (0);
		OLDPWD->next = NULL;
		OLDPWD->var = ft_strdup("OLDPWD=");
		env->next = OLDPWD;
		i++;
	}
}

int	builtin_cd(t_cmd *cmd, t_env *tmp)
{
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
		if (tmp != NULL)
		{
			str = ft_strdup((tmp->var + 5));
			chdir(str);
			free(str);
			return (0);
		}
		write(2, "minishell: cd: HOME not set\n", 17);
		return (1);
	}
}