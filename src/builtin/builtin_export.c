/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:16:07 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/10 10:53:07 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int	read_env(t_env *env)
{
	int	i;

	while (env)
	{
		i = 0;
		printf("declare -x ");
		while (env->var[i] != '=' && env->var[i])
		{
			printf("%c", env->var[i]);
			i++;
		}
		if (env->var[i])
			printf("%c\'", env->var[i]);
		i++;
		while (env->var[i])
		{
			printf("%c", env->var[i]);
			i++;
		}
		printf("\'\n");
		env = env->next;
	}
	return (0);
}

size_t	same_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	rule_env(char *str, t_env *tmp)
{
	while (tmp)
	{
		if (ft_strncmp(tmp->var, str, same_env(tmp->var)) == 0)
		{
			if (ft_strlen(str) == same_env(str))
				return (0);
			free(tmp->var);
			tmp->var = ft_strdup(str);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	not_valid_export(char *str)
{
	if (str[0] == '_')
		return (1);
	write(2, "export: ", 8);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 25);
	return (1);
}

int	builtin_export(t_cmd *cmd, t_env *env, int i, int j)
{
	t_env	*node;

	if (cmd->option[1] == NULL)
		return (read_env(env));
	node = (env);
	while (node->next)
		node = node->next;
	while (cmd->option[++i])
	{
		if (ft_isalpha(cmd->option[i][0]) == 0)
		{
			j = not_valid_export(cmd->option[i]);
			continue ;
		}
		if (rule_env(cmd->option[i], env) == 1)
		{
			node->next = malloc(sizeof(t_env));
			if (node->next == 0)
				return (0);
			node->next->var = ft_strdup(cmd->option[i]);
			node->next->next = NULL;
			node = node->next;
		}
	}
	return (j);
}
