/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:38:22 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/29 15:58:16 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"

static t_env	*get_env_list_util(char *env_var)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (env_node == NULL)
		error_malloc();
	if (env_var == NULL)
		env_node->var = ft_strdup("");
	else
		env_node->var = ft_strdup(env_var);
	if (env_node->var == NULL)
		error_malloc();
	env_node->next = NULL;
	return (env_node);
}

t_env	*get_env_list(char **env)
{
	size_t	i;
	t_env	*env_list;
	t_env	*node;

	if (env == NULL || env[0] == NULL)
		return (get_env_list_util(NULL));
	env_list = get_env_list_util(env[0]);
	node = env_list;
	i = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		{
			node->next = get_env_list_util(env[i]);
			node = node->next;
		}
	}
	return (env_list);
}

char	**env_array_size(t_env *env)
{
	size_t	count;
	char	**env_array;

	count = 0;
	while (env)
	{
		env = env->next;
		++count;
	}
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (env_array == NULL)
		error_malloc();
	return (env_array);
}

char	**get_env_array(t_env *env)
{
	char	**env_array;
	int		i;

	if (env->var[0] == '\0')
		return (NULL);
	env_array = env_array_size(env);
	i = 0;
	while (env)
	{
		env_array[i] = ft_strdup(env->var);
		if (env_array[i] == NULL)
			error_malloc();
		++i;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
