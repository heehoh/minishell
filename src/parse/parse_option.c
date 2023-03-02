/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:05:58 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/02 13:43:03 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

void	is_cmd_or_file(char **sep_pipe, int *flag)
{
	(*flag) = CMD;
	while (**sep_pipe == ' ')
		(*sep_pipe)++;
	if (**sep_pipe == '<' || **sep_pipe == '>')
	{
		if ((*sep_pipe)[1] == '<' || (*sep_pipe)[1] == '>')
			(*sep_pipe)++;
		(*flag) = FILE_;
		(*sep_pipe)++;
	}
	while (**sep_pipe == ' ')
		(*sep_pipe)++;
}

int	num_option(char *sep_pipe)
{
	int		count;
	int		flag;
	int		quote_flag;

	count = 0;
	quote_flag = 0;
	while (*sep_pipe)
	{
		is_cmd_or_file(&sep_pipe, &flag);
		while ((*sep_pipe != ' ' && *sep_pipe) || quote_flag)
		{
			flag_quote(sep_pipe, &quote_flag);
			if ((*sep_pipe == '<' || *sep_pipe == '>') && quote_flag == 0)
				break ;
			sep_pipe++;
		}
		if (flag == 0 && sep_pipe[-1] != ' ')
			count++;
	}
	return (count);
}

void	cmd_word_count(char **option, char *sep_pipe, int quote_flag)
{
	int		word_count;
	int		is_cmd;
	int		i;

	i = 0;
	while (*sep_pipe)
	{
		word_count = 0;
		is_cmd_or_file(&sep_pipe, &is_cmd);
		while (*sep_pipe && (*sep_pipe != ' ' || quote_flag))
		{
			flag_quote(sep_pipe, &quote_flag);
			if ((*sep_pipe == '<' || *sep_pipe == '>') && quote_flag == 0)
				break ;
			word_count++;
			sep_pipe++;
		}
		if (is_cmd == CMD && sep_pipe[-1] != ' ')
		{
			option[i] = malloc(sizeof(char) * word_count + 1);
			if (option[i] == NULL)
				return ;
			i++;
		}
	}
}


void	put_cmd_option(char **option, char *sep_pipe, int quote_flag)
{
	int		word_count;
	int		is_cmd;
	int		i;

	i = 0;
	while (*sep_pipe)
	{
		word_count = 0;
		is_cmd_or_file(&sep_pipe, &is_cmd);
		while (*sep_pipe && (*sep_pipe != ' ' || quote_flag))
		{
			flag_quote(sep_pipe, &quote_flag);
			if ((*sep_pipe == '<' || *sep_pipe == '>') && quote_flag == 0)
				break ;
			if (is_cmd == CMD && option[i])
				option[i][word_count] = *sep_pipe;
			word_count++;
			sep_pipe++;
		}
		if (is_cmd == CMD && sep_pipe[-1] != ' ')
		{
			option[i][word_count] = '\0';
			i++;
		}
	}
}

char	**parse_cmd_option(char *sep_pipe)
{
	char	**option;
	char	*str;
	int		count;

	count = num_option(sep_pipe); // num_option이 0일 때 처리해야함??
	option = (char **)malloc(sizeof(char *) * (count + 1));
	if (option == 0)
		return (0);
	option[count] = NULL;
	cmd_word_count(option, sep_pipe, 0);
	put_cmd_option(option, sep_pipe, 0);
	return (option);
}

