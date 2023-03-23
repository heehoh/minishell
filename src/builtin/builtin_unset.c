/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:19:05 by migo              #+#    #+#             */
/*   Updated: 2023/03/23 16:51:42 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../process.h"

int	cp_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i - 1);
}

int	frist_env(t_process *process, t_env *tmp, t_current *current)
{
	current->env = tmp->next;
	free(tmp->var);
	free (tmp);
	process->env = current->env;
	return (1);
}

void	free_env(t_env *env, t_env *tmp)
{
	env->next = tmp->next;
	free(tmp->var);
	free(tmp);
}

int	not_valid_unset(char *str)
{
	if (str[0] == '_')
		return (1);
	write(2, "unset: ", 8);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 25);
	return (1);
}

int	builtin_unset(t_process *process, int i, int j, t_current *current)
{
	t_env	*tmp;
	t_env	*pre_tmp;
	t_cmd	*cmd;

	cmd = process->cmd;
	if (cmd->option[1] == NULL)
		return (0);
	while (cmd->option[++i])
	{
		if (ft_isalpha(cmd->option[i][0]) == 0)
			j = not_valid_unset(cmd->option[i]);
		tmp = process->env;
		if (ft_strncmp(cmd->option[i], tmp->var, cp_env(tmp->var)) == 0
			&& frist_env(process, tmp, current))
			continue ;
		while (tmp)
		{
			pre_tmp = tmp;
			tmp = tmp->next;
			if (tmp != NULL
				&& ft_strncmp(cmd->option[i], tmp->var, cp_env(tmp->var)) == 0)
				free_env(pre_tmp, tmp);
		}
	}
	return (j);
}
