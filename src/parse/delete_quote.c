/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:30:59 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/26 12:53:16 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	cnt_except_quote(char *str)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*str)
	{
		if (flag_quote(str, &quote_flag) == 0)
			++count;
		++str;
	}
	return (count);
}

void	insert_except_quote(char *prev, char *str)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*prev)
	{
		if (flag_quote(prev, &quote_flag) == 0)
		{
			str[count] = *prev;
			count++;
		}
		prev++;
	}
}

void	delete_quote_util(char **str)
{
	char	*prev;
	int		count;

	prev = *str;
	if (*str != NULL)
		count = cnt_except_quote(*str);
	else
		count = 0;
	*str = malloc(sizeof(char) * (count + 1));
	if (*str == NULL)
		error_malloc();
	(*str)[count] = '\0';
	insert_except_quote(prev, *str);
	free(prev);
}

void	delete_quote(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->option[i])
		{
			delete_quote_util(&(cmd->option[i]));
			++i;
		}
		i = 0;
		while (cmd->file[i].name)
		{
			delete_quote_util(&(cmd->file[i].name));
			++i;
		}
		cmd = cmd->next;
	}
}
