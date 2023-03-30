/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:16:07 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/30 11:38:44 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../process.h"

int	read_env(t_env *env, int write_fd)
{
	while (env)
	{
		write(write_fd, "declare -x ", 11);
		write(write_fd, env->var, ft_strlen(env->var));
		write(write_fd, "\n", 1);
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
		if (ft_strncmp(tmp->var, str, same_env(tmp->var)) == 0
			&& ft_strncmp(tmp->var, str, same_env(str)) == 0)
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
	write(2, "export: ", 8);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 25);
	return (1);
}

int	builtin_export(t_process *process, int i, int j, int write_fd)
{
	t_env	*node;
	t_cmd	*cmd;

	cmd = process->cmd;
	if (cmd->option[1] == NULL)
		return (read_env(process->env, write_fd));
	node = (process->env);
	while (node->next)
		node = node->next;
	while (cmd->option[++i])
	{
		if (ft_isalpha(cmd->option[i][0]) == 0)
			j = not_valid_export(cmd->option[i]);
		else if (rule_env(cmd->option[i], process->env) == 1)
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
