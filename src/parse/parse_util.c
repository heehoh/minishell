/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:33:03 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/02 13:42:05 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	dimen_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}
