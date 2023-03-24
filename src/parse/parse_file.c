/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:34:59 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/24 18:18:06 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"

int	num_file(char *sep_pipe)
{
	int	i;
	int	quote_flag;
	int	count;

	i = 0;
	count = 0;
	quote_flag = 0;
	while (sep_pipe[i])
	{
		flag_quote(&(sep_pipe[i]), &quote_flag);
		if (sep_pipe[i] == '<' && quote_flag == 0)
		{
			if (sep_pipe[i + 1] == '<')
				i++;
			count++;
		}
		else if (sep_pipe[i] == '>' && quote_flag == 0)
		{
			if (sep_pipe[i + 1] == '>')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

void	put_redir(t_file *file, char *sep_pipe, int quote_flag, int fl_num)
{
	int	count;

	count = 0;
	while (*sep_pipe && count < fl_num)
	{
		file[count].redirection = 0;
		flag_quote(sep_pipe, &quote_flag);
		if ((*sep_pipe == '<' && sep_pipe[1] == '<') && quote_flag == 0)
		{
			file[count].redirection = 1;
			sep_pipe++;
		}
		else if (*sep_pipe == '<' && sep_pipe[1] != '<' && quote_flag == 0)
				file[count].redirection = 2;
		else if (*sep_pipe == '>' && sep_pipe[1] != '>' && quote_flag == 0)
			file[count].redirection = 3;
		else if (*sep_pipe == '>' && sep_pipe[1] == '>' && quote_flag == 0)
		{
			file[count].redirection = 4;
			sep_pipe++;
		}
		sep_pipe++;
		if (file[count].redirection != 0)
			count++;
	}
}

void	fl_word_count(t_file *file, char *sep_pipe, int quote_flag, int fl_num)
{
	int		word_count;
	int		is_file;
	int		i;

	i = 0;
	while (*sep_pipe && i < fl_num)
	{
		word_count = 0;
		is_cmd_or_file(&sep_pipe, &is_file);
		while (*sep_pipe && (ft_is_space(*sep_pipe) == 0 || quote_flag))
		{
			flag_quote(sep_pipe, &quote_flag);
			if ((*sep_pipe == '<' || *sep_pipe == '>') && quote_flag == 0)
				break ;
			word_count++;
			sep_pipe++;
		}
		if (is_file == FILEFLAG)
		{
			file[i].name = malloc(sizeof(char) * word_count + 1);
			if (file[i].name == NULL)
				error_malloc();
			i++;
		}
	}
}

void	put_file(t_file *file, char *sep_pipe, int quote_flag, int fl_num)
{
	int		file_count;
	int		is_file;
	int		i;

	i = 0;
	while (*sep_pipe && i < fl_num)
	{
		file_count = 0;
		is_cmd_or_file(&sep_pipe, &is_file);
		while ((ft_is_space(*sep_pipe) == 0 && *sep_pipe) || quote_flag)
		{
			flag_quote(sep_pipe, &quote_flag);
			if ((*sep_pipe == '<' || *sep_pipe == '>') && quote_flag == 0)
				break ;
			if (is_file == 1 && file[i].redirection != 0)
				file[i].name[file_count] = *sep_pipe;
			file_count++;
			sep_pipe++;
		}
		if (is_file == FILEFLAG)
		{
			file[i].name[file_count] = '\0';
			i++;
		}
	}
}

t_file	*parse_file(char *sep_pipe)
{
	t_file	*file;
	int		count;

	count = num_file(sep_pipe);
	file = malloc(sizeof(t_file) * (count + 1));
	if (file == NULL)
		error_malloc();
	file[count].name = NULL;
	file[count].redirection = 0;
	if (count == 0)
		return (file);
	fl_word_count(file, sep_pipe, 0, count);
	put_redir(file, sep_pipe, 0, count);
	put_file(file, sep_pipe, 0, count);
	return (file);
}
