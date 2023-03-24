/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:39:41 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/24 18:03:08 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../process.h"
#include "../../libft/libft.h"

char	**get_path(t_env *env)
{
	char	**path;

	if (env == NULL)
		return (NULL);
	while (env)
	{
		if (ft_strncmp("PATH=", env->var, 5) == 0)
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (NULL);
	path = ft_split(env->var + 5, ':');
	if (path == NULL)
		error_malloc();
	return (path);
}

static void	ft_free(char **path, char *cmd)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		++i;
	}
	free(path);
	free(cmd);
}

char	*cmd_with_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_without_path;
	char	*cmd_with_path;

	cmd_without_path = ft_strjoin("/", cmd);
	if (cmd_without_path == NULL)
		error_malloc();
	i = -1;
	while (path[++i])
	{
		cmd_with_path = ft_strjoin(path[i], cmd_without_path);
		if (cmd_with_path == NULL)
			error_malloc();
		if (access(cmd_with_path, F_OK) == 0)
		{
			ft_free(path, cmd_without_path);
			if (access(cmd_with_path, X_OK) == -1)
				error_access(cmd_with_path);
			return (cmd_with_path);
		}
		free(cmd_with_path);
	}
	ft_free(path, cmd_without_path);
	error_cmd_not_found(cmd);
	return (NULL);
}

char	*get_command(char *cmd, t_env *env)
{
	int		i;
	char	**path;

	i = 0;
	if (cmd[0] == '\0')
		error_cmd_not_found(cmd);
	path = get_path(env);
	while (cmd[i])
	{
		if (cmd[i] == '/' || path == NULL)
		{
			if (access(cmd, F_OK) == -1)
				error_access(cmd);
			if (access(cmd, X_OK) == -1)
				error_access(cmd);
			else
				return (cmd);
		}
		++i;
	}
	return (cmd_with_path(cmd, path));
}
