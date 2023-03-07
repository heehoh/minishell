/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wave.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:25:17 by migo              #+#    #+#             */
/*   Updated: 2023/03/07 21:13:08 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	cnt_wave(char *str)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*str)
	{
		flag_quote(str, &quote_flag);
		if (*str == '~' && quote_flag == 0)
		{
			if (str[1] == '/' || str[1] == ' ' || str[1] == '\0')
				count += 4;
		}
		str++;
		count++;
	}
	return (count);
}

void	insert_wave(char *pre, char *str)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*pre)
	{
		flag_quote(pre, &quote_flag);
		if (*pre == '~' && quote_flag == 0)
		{
			if (pre[1] == '/' || pre[1] == ' ' || pre[1] == '\0')
			{
				str[count] = '$';
				str[count + 1] = 'H';
				str[count + 2] = 'O';
				str[count + 3] = 'M';
				str[count + 4] = 'E';
				count += 5;
			}
			pre++;
		}
		str[count] = *pre;
		pre++;
		count++;
	}
}

void	replace_wave(char **str)
{
	char	*prev;
	int		count;

	prev = *str;
	count = cnt_wave(*str);
	*str = malloc(sizeof(char) * (count + 1));
	if (*str == NULL)
		return ;
	(*str)[count] = '\0';
	insert_wave(prev, *str);
	free(prev);
}

void	consider_wave(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = -1;
		while (cmd->option[++i])
			replace_wave(&(cmd->option[i]));
		i = -1;
		while (cmd->file[++i].name)
			replace_wave(&(cmd->file[i].name));
		cmd = cmd->next;
	}
}
