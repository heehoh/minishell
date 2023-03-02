/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:23:40 by migo              #+#    #+#             */
/*   Updated: 2023/03/02 14:47:05 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	read_env(t_env *env)
{
	while (env)
	{
		printf("declare -x ");
		printf("%s\n", env->var);
		env = env->next;
	}
}

void	builtin_export(t_cmd *cmd)
{
	int		i;
	t_env	*node;

	i = 0;
	node = g_global;
	if (ft_strncmp((cmd->option[0]), "export", ft_strlen(cmd->option[0])) == 0)
	{
		while (node->next)
			node = node->next;
		if (cmd->option[1] != NULL)
		{
			node->next = malloc(sizeof(t_env));
			if (node->next == 0)
				return (0);
			node->next->var = ft_strdup(cmd->option[1]);
			node->next->next = NULL;
		}
		else
		{
			read_env(g_global);
		}
	}
}