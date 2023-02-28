/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:38:22 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/28 11:55:11 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	get_env_list(char **env)
{
	size_t	i;
	t_env	*node;

	g_global = (t_env *)malloc(sizeof(t_env));
	g_global->env = ft_strdup(env[0]);
	node = g_global;
	i = 0;
	while (env[++i])
	{
		node->next = (t_env *)malloc(sizeof(t_env));
		node->next->env = ft_strdup(env[i]);
		node = node->next;
	}
	node->next = NULL;
}

void	builtin_env(t_cmd *cmd)
{
	t_env	*env;

	env = g_global;
	while (env)
	{
		printf("%s\n", env->env);
		env = env->next;
	}
}

void	builtin_unset(char *env)
{
	t_env	*node;

	node = g_global;
	if (ft_strncmp(node->env, env, ft_strlen(env)) == 0)
	{
		g_global = g_global->next;
		free(node->env);
		free(node);
	}
	while ()
}