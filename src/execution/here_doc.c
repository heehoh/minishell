/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:19:48 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/30 11:52:21 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../libft/libft.h"
#include "../minishell.h" 
#include <dirent.h>

char	*get_tmp_dir(t_env *env)
{
	char	*tmp_dir;
	DIR		*dir_info;

	while (env)
	{
		if (ft_strncmp("TMPDIR=", env->var, 7) == 0)
			break ;
		env = env->next;
	}
	if (env != NULL)
	{
		tmp_dir = ft_strdup(env->var + 7);
		if (tmp_dir == NULL)
			error_malloc();
		dir_info = opendir(tmp_dir);
		if (dir_info == NULL)
			return (NULL);
		if (closedir(dir_info) == -1)
			perror("minishell: heredoc close error");
		return (tmp_dir);
	}
	return (NULL);
}

char	*tmp_file_name(char *tmp_file, int num, t_env *env)
{
	char	*tmp_dir;
	char	*number;

	number = ft_itoa(num);
	if (number == NULL)
		error_malloc();
	tmp_dir = get_tmp_dir(env);
	tmp_file = ft_strjoin(tmp_dir, number);
	if (tmp_file == NULL)
		error_malloc();
	free(number);
	free(tmp_dir);
	return (tmp_file);
}

void	here_doc_write(char *limiter, char *tmp_file)
{
	int		fd;
	char	*str;
	char	*str_with_newline;

	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_open(tmp_file);
	while (1)
	{
		str = readline("> ");
		if (str == NULL || (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
				&& ft_strncmp(str, limiter, ft_strlen(str)) == 0))
		{
			free(str);
			close(fd);
			return ;
		}
		str_with_newline = ft_strjoin(str, "\n");
		free(str);
		write(fd, str_with_newline, ft_strlen(str_with_newline));
		free(str_with_newline);
	}
}

void	here_doc_file(t_cmd *cmd, t_env *env, int is_child)
{
	int		cmd_count;
	int		file_count;
	char	*tmp_file;

	cmd_count = 0;
	while (cmd)
	{
		file_count = 0;
		tmp_file = NULL;
		while (cmd->file[file_count].redirection)
		{
			if (cmd->file[file_count].redirection == 1)
			{
				tmp_file = tmp_file_name(tmp_file, cmd_count, env);
				if (is_child == 1)
					here_doc_write(cmd->file[file_count].name, tmp_file);
				free(cmd->file[file_count].name);
				cmd->file[file_count].name = tmp_file;
			}
			++file_count;
		}
		cmd = cmd->next;
		++cmd_count;
	}
}

int	here_doc_fork(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_fork();
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		here_doc_file(cmd, env, 1);
		exit(0);
	}
	wait(&status);
	if (WIFSIGNALED(status))
	{
		printf("\n");
		return (1);
	}
	here_doc_file(cmd, env, 0);
	return (0);
}
