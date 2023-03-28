/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:33:03 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/28 15:09:28 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	flag_quote(char *sep_pipe, int *quote_flag)
{
	int	prev_quote_flag;

	prev_quote_flag = *quote_flag;
	if (*sep_pipe == '\'')
	{
		if (*quote_flag == 0)
			*quote_flag = 1;
		else if (*quote_flag == 1)
			*quote_flag = 0;
	}
	else if (*sep_pipe == '\"')
	{
		if (*quote_flag == 0)
			*quote_flag = 2;
		else if (*quote_flag == 2)
			*quote_flag = 0;
	}
	if (prev_quote_flag != *quote_flag)
		return (1);
	return (0);
}

void	str_array_clear(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		++i;
	}
	free(str);
}

void	cmd_clear(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		str_array_clear(cmd->option);
		i = 0;
		while (cmd->file[i].redirection)
		{
			if (cmd->file[i].redirection == 1)
				if (access(cmd->file[i].name, F_OK) == 0)
					unlink(cmd->file[i].name);
			free(cmd->file[i].name);
			i++;
		}
		free(cmd->file);
		free(cmd);
		cmd = tmp;
	}
}
