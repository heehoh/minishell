/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:19:05 by migo              #+#    #+#             */
/*   Updated: 2023/03/24 18:17:52 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../process.h"

int	not_valid_unset(char *str);

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
	return (i);
}

int	frist_env(t_process *process, t_env *tmp, t_current *current)
{
	current->env = tmp->next;
	free(tmp->var);
	free (tmp);
	process->env = current->env;
	return (1);
}

int	free_env(t_env *env, t_env *tmp)
{
	if (tmp->next == NULL)
		env->next = NULL;
	else
		env->next = tmp->next;
	free(tmp->var);
	free(tmp);
	return (1);
}

int	is_env(char *option, char *env)
{
	if (ft_strncmp(option, env, cp_env(env)) == 0
		&& ft_strncmp(option, env, ft_strlen(option)) == 0)
		return (1);
	return (0);
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
		if (is_env(cmd->option[i], tmp->var)
			&& frist_env(process, tmp, current))
			continue ;
		while (tmp)
		{
			pre_tmp = tmp;
			tmp = tmp->next;
			if (tmp != NULL && is_env(cmd->option[i], tmp->var)
				&& free_env(pre_tmp, tmp))
				break ;
		}
	}
	return (j);
}
