/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:16:07 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/07 20:16:12 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_isalpha(int c)
{
	if (65 <= c && c <= 90)
		return (1);
	else if (97 <= c && c <= 122)
		return (1);
	else
		return (0);
	return (0);
}

int	read_env(t_env *env)
{
	while (env)
	{
		printf("declare -x ");
		printf("%s\n", env->var);
		env = env->next;
	}
	return (0);
}

int	same_env(char *str)
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

int	builtin_export(t_cmd *cmd, t_env *env)
{
	int		i;
	t_env	*node;

	i = 0;
	if (cmd->option[1] == NULL)
		return (read_env(env));
	if (ft_isalpha(cmd->option[1][0]) == 0)
	{
		printf("export: \'%s\': not a valid identifier\n", cmd->option[1]);
		return (1);
	}
	node = (env);
	while (node->next)
		node = node->next;
	while (cmd->option[++i])
	{
		if (rule_env(cmd->option[i], env) == 1)
		{
			node->next = malloc(sizeof(t_env));
			if (node->next == 0)
				return ;
			node->next->var = ft_strdup(cmd->option[i]);
			node->next->next = NULL;
			node = node->next;
		}
	}
	return (0);
}
