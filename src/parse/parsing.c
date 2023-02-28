/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:27:55 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/28 17:11:31 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	count_file(char *cmd_set)
{
	int	count;

	count = 0;
	while (*cmd_set)
	{
		if (*cmd_set == '<' && cmd_set[1] == '<')
		{
			++count;
			++cmd_set;
		}
		else if (*cmd_set == '<' && cmd_set[1] != '<')
			++count;
		else if (*cmd_set == '>' && cmd_set[1] != '>')
			++count;
		else if (*cmd_set == '>' && cmd_set[1] == '>')
		{
			++count;
			++cmd_set;
		}
		++cmd_set;
	}
	return (count);
}

int	count_option(char *cmd_set)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd_set[i])
	{
		while (cmd_set[i] && cmd_set[i] == '<' || cmd_set[i] == '>'
			|| cmd_set[i] == ' ')
			++i;
		while (cmd_set[i] && !(cmd_set[i] == '<' || cmd_set[i] == '>'
				|| cmd_set[i] == ' '))
			++i;
		++count;
	}
	return (count - count_file(cmd_set));
}

int	redir_type(char *redir)
{
	if (*redir == '<' && redir[1] == '<')
		return (1);
	if (*redir == '<' && redir[1] != '<')
		return (2);
	if (*redir == '>' && redir[1] != '>')
		return (3);
	if (*redir == '>' && redir[1] == '>')
		return (4);
	return (0);
}

void	get_file(char **str, t_file *file, int redir)
{
	int	i;
	int	qoute_flag;

	file->redirection = redir;
	if (*str == '<' || *str == '>')
		++str;
	if (*str == '<' || *str == '>')
		++str;
	i = 0;
	while (str[i])
		++i;
	file->name = (char *)malloc(sizeof(char) * (i + 1));
	file->name[i] = '\0';
	while (str[--i])
		file->name[i] = str[i];
}

void	get_cmd(char *str, char **option)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	*option = (char *)malloc(sizeof(char) * (i + 1));
	(*option)[i] = '\0';
	while (str[--i])
		(*option)[i] = str[i];
}

void	make_set(char *cmd_set, t_cmd *cmd, int file_cnt, int op_cnt)
{
	char	**s;

	cmd->file = (t_file *)malloc(sizeof(t_file) * (count_file(cmd_set) + 1));
	cmd->option = (char **)malloc(sizeof(char *) * (count_option(cmd_set) + 1));
	s = ft_split(cmd_set, ' ');
	while (*s)
	{
		while (**s)
		{
			if (**s == '<' || **s == '>')
			{
				if ((*s)[1] == '\0')
					get_file(*s, &(cmd->file[file_cnt++]), redir_type(*s));
				else if (((*s)[1] == '<' || (*s)[1] == '>') && (*s)[2] == '\0')
					get_file(*s, &(cmd->file[file_cnt++]), redir_type(*s));
				else
					get_file(*s, &(cmd->file[file_cnt++]), redir_type(*s));
			}
			else
				get_cmd(*s, &(cmd->option[op_cnt++]));
		}
		++(*s);
	}
	cmd->option[op_cnt] = NULL;
	cmd->file[file_cnt].name = NULL;
}

#include <stdio.h>

int	main(void)
{
	char	*cmd_set = "<<a<    b <'c   sjfhklsdj' cat       ";
	t_cmd	cmd;
	int		i;

	make_set(cmd_set, &cmd, 0, 0);
	i = -1;
	while (cmd.option[++i])
		printf("%s\n", cmd.option[i]);
	i = -1;
	while (cmd.file[++i].name)
	{
		printf("%d : ", cmd.file[i].redirection);
		printf("%s\n", cmd.file[i].name);
	}
	return (0);
}
