/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:23:40 by migo              #+#    #+#             */
/*   Updated: 2023/03/02 17:16:04 by migo             ###   ########.fr       */
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

void	read_env(t_env *env)
{
	while (env)
	{
		printf("declare -x ");
		printf("%s\n", env->var);
		env = env->next;
	}
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

int	rule_env(char *str, t_env *env)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && ft_isalpha(str[0]))
		{
			while (env)
			{
				if (ft_strncmp(env->var, str, same_env(str)) == 0)
					return (0);
				env = env->next;
			}
			return (1);
		}
		i++;
	}
	if (ft_isalpha(str[0]) == 0)
		printf("export: \'%s\': not a valid identifier\n", str);
	return (0);
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
		while (cmd->option[++i])
		{
			if (rule_env(cmd->option[i], g_global) == 1)
			{
				node->next = malloc(sizeof(t_env));
				if (node->next == 0)
					return ;
				node->next->var = ft_strdup(cmd->option[i]);
				node->next->next = NULL;
				node = node->next;
			}
		}
		if (cmd->option[1] == NULL)
			read_env(g_global);
	}
}