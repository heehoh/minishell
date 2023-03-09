/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:38:22 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/09 18:37:29 by hujeong          ###   ########.fr       */
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
		node->next = get_env_list_util(env[i]);
		node = node->next;
	}
	node->next = NULL;
	return (env_list);
}

char	**get_env_array(t_env *env)
{
	size_t	count;
	t_env	*node;
	char	**env_array;

	node = env;
	count = 0;
	while (node)
	{
		node = node->next;
		++count;
	}
	if (count > 0)
		env_array = (char **)malloc(sizeof(char *) * (count + 1));
	else
		return (NULL);
	if (env_array == NULL)
		error_malloc();
}
