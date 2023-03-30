/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:44:28 by migo              #+#    #+#             */
/*   Updated: 2023/03/30 13:40:36 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <fcntl.h>

size_t	same_env(char *str);
int		rule_env(char *str, t_env *tmp);
int		no_directory(char *str);
int		no_file_directory(char *str);
void	not_have_path(void);

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

int	pwd(t_current *current, t_env *env, t_env *tmp, char *pwd)
{
	char		path[1024];
	static int	flag;

	if (rule_env("OLDPWD=", env) == 1 && flag++ == 0)
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
		not_have_path();
		return (1);
	}
	getcwd(current->path, 1024);
	pwd = ft_strjoin("PWD=", current->path);
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
	while (current->path[i])
		i++;
	if (str[0] != '.' || (current->path[0] != '\0' && current->path[0] != '.'))
		current->path[i++] = '/';
	while (str[j] && (str[0] != '.' || current->path[0] != '.'))
		current->path[i++] = str[j++];
	current->path[i] = '\0';
	if (chdir(str) < 0)
		return (no_directory(str));
	else
		return (pwd(current, env, env, NULL));
}

int	builtin_cd(t_cmd *cmd, t_env *tmp, t_current *current)
{
	char	*str;

	if (cmd->option[1] != NULL)
		return (cd_option(cmd->option[1], 0, tmp, current));
	else
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->var, "HOME=", 5) == 0)
			{
				str = ft_strdup((tmp->var + 5));
				if (chdir(str) < 0 && no_directory(str))
				{
					free(str);
					return (1);
				}
				free(str);
				return (pwd(current, current->env, current->env, NULL));
			}
			tmp = tmp->next;
		}
		write (2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
}
