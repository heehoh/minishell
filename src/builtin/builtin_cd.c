/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:44:28 by migo              #+#    #+#             */
/*   Updated: 2023/03/24 13:36:37 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <fcntl.h>
#include <stdio.h>

size_t	same_env(char *str);
int		rule_env(char *str, t_env *tmp);
int		no_directory(char *str);
int		no_file_directory(char *str);

int	rule_cd(char *str, char *path)
{
	if (access(str, F_OK) != 0)
		return (no_file_directory(str));
	if (access(str, X_OK) != 0)
	{
		write(2, "cd: permission denied: ", 23);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		return (0);
	}
	if (ft_strlen(str) + ft_strlen(path) > 1024)
	{
		write(2, "minishell: cd: path is too long\n", 32);
		return (0);
	}
	return (1);
}

void	make_env(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	tmp->var = ft_strdup(str);
	tmp->next = NULL;
	while (env->next)
		env = env->next;
	env->next = tmp;
}

int	pwd(char *path, t_env *env, t_env *tmp)
{
	char	*pwd;

	pwd = NULL;
	if (rule_env("OLDPWD=", env) == 1)
		make_env(env, "OLDPWD=");
	while (env)
	{
		if (ft_strncmp(env->var, "PWD=", 4) == 0)
			pwd = ft_strjoin("OLDPWD=", (env->var + 4));
		env = env->next;
	}
	if (pwd != NULL)
		rule_env(pwd, tmp);
	free(pwd);
	if (getcwd(path, 1024) == NULL)
	{
		write(2, "chdir: error retrieving current directory:", 40);
		write(2, "getcwd: cannot access parent directories", 41);
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	pwd = ft_strjoin("PWD=", path);
	rule_env(pwd, tmp);
	free(pwd);
	return (0);
}

int	cd_option(char *str, int i, t_env *env, t_current *current)
{
	int	j;

	j = 0;
	if (rule_cd(str, current->path) == 0)
		return (1);
	if (str[0] == '/')
	{
		if (chdir(str) < 0)
			return (no_directory(str));
		else
			return (pwd(current->path, env, env));
	}
	while (current->path[i])
		i++;
	current->path[i] = '/';
	i++;
	while (str[j])
		current->path[i++] = str[j++];
	current->path[i] = str[j];
	if (chdir(str) < 0)
		return (no_directory(str));
	else
		return (pwd(current->path, env, env));
}

int	builtin_cd(t_cmd *cmd, t_env *tmp, t_current *current)
{
	char	*str;

	if (cmd->option[1] != NULL)
	{
		return (cd_option(cmd->option[1], 0, tmp, current));
	}
	else
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->var, "HOME=", 5) == 0)
			{
				str = ft_strdup((tmp->var + 5));
				if (chdir(str) < 0)
					return (no_directory(str));
				free(str);
				return (0);
			}
			tmp = tmp->next;
		}
		write (2, "minishell: cd: HOME not set", 27);
		return (1);
	}
}
