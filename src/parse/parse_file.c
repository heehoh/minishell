/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:34:59 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/02 14:51:47 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

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
		flag_quote(sep_pipe, &quote_flag);
		if (sep_pipe[i] == '<' && quote_flag == 0)
		{
			if (sep_pipe[i + 1] == '<')
				i++;
			count++;
		}
		else if (sep_pipe[i] == '>' && quote_flag == 0) /*if -> else if*/
		{
			if (sep_pipe[i + 1] == '>')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

void	put_redirection(t_file *file, char *sep_pipe, int quote_flag)
{
	int	count;

	count = 0;
	while (*sep_pipe)
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

void	file_word_count(t_file *file, char *sep_pipe, int quote_flag)
{
	int		word_count;
	int		is_file;
	int		i;

	i = 0;
	while (*sep_pipe)
	{
		word_count = 0;
		is_cmd_or_file(&sep_pipe, &is_file);
		while (*sep_pipe && (*sep_pipe != ' '|| quote_flag)) /*바꿈*/
		{
			flag_quote(sep_pipe, &quote_flag);
			if ((*sep_pipe == '<' || *sep_pipe == '>') && quote_flag == 0)
				break ;
			word_count++;
			sep_pipe++;
		}
		if (is_file == FILE_ && sep_pipe[-1] != ' ')
		{
			file[i].name = malloc(sizeof(char) * word_count + 1);
			if (file[i].name == NULL)
				return ;
			i++;
		}
	}
}

void	put_file(t_file *file, char *sep_pipe, int quote_flag)
{
	int		file_count;
	int		is_file;
	int		i;

	i = 0;
	while (*sep_pipe)
	{
		file_count = 0;
		is_cmd_or_file(&sep_pipe, &is_file);
		while ((*sep_pipe != ' ' && *sep_pipe) || quote_flag)
		{
			flag_quote(sep_pipe, &quote_flag);
			if ((*sep_pipe == '<' || *sep_pipe == '>') && quote_flag == 0)
				break ;
			if (is_file == 1 && file[i].redirection != 0)
				file[i].name[file_count] = *sep_pipe;
			file_count++;
			sep_pipe++;
		}
		if (is_file == FILE_)
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
	file = malloc(sizeof(t_file) * (count + 1)); // file이 0개일 때 처리
	if (file == 0)
		return (0);
	file[count].name = NULL;
	file[count].redirection = 0;
	file_word_count(file, sep_pipe, 0);
	put_redirection(file, sep_pipe, 0);
	put_file(file, sep_pipe, 0);
	return (file);
}
