/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:19:48 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/05 16:13:37 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include "./src/libft/libft.h"
#include "./src/minishell.h"

char	*get_tmp_dir(t_env *env)
{
	char	*tmp_dir;

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
		return (tmp_dir);
	}
	return (NULL);
}

char	*tmp_file_name(char *tmp_file, int num, t_env *env)
{
	char	*tmp_dir;
	char	*number;

	free(tmp_file);
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

	fd = open(tmp_file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		error_open();
	while (1)
	{
		str = readline("> ");
		if (str == NULL || ft_strncmp(str, limiter, ft_strlen(str)) == 0)
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

void	here_doc_file(t_cmd *cmd, t_env *env)
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
				if (tmp_file == NULL)
					error_malloc();
				hear_doc_write(cmd->file[file_count].name, tmp_file);
				free(cmd->file[file_count].name);
				cmd->file[file_count].name = tmp_file;
			}
			++file_count;
		}
		cmd = cmd->next;
	}
}

//파싱된 커멘드 셋 받음
//그 안에 히어독 있는지 검사 -> 이중반복문으로 순회하면서 히어독 오픈 here_doc_file
//tmpdir strjoin 해서 here_doc 파일 만듦.
//pid cmd 개수만큼 malloc
//pipe 2 * (cmd 개수 -1) malloc
//pipe 오픈
//fork
//dup2로 파일 입출력 방향 전환
//안쓰는 pipe 닫고 
//wait

//$? 파싱에서 해결해야 함함