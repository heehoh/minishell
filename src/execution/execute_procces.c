/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_procces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:51:42 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/05 17:27:03 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

#include "../minishell.h"
#include <fcntl.h>

int	cmd_count(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		cmd = cmd->next;
		++count;
	}
	return (count);
}

void	open_pipe(int *pipe_fd, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(&(pipe_fd[2 * i])) < 0)
			error_pipe();
		++i;
	}
}

void	parent_process(t_cmd *cmd, t_env *env)
{
	pid_t	*pid;
	int		*pipe;
	int		count;
	int		i;

	count = cmd_count(cmd);
	pid = (pid_t *)malloc(sizeof(pid_t) * count);
	if (pid == NULL)
		error_malloc();
	if (count > 1)
	{
		pipe = (int *)malloc(sizeof(int) * (count - 1) * 2);
		if (pipe == NULL)
			error_malloc();
		open_pipe(pipe, count -1);
	}
	here_doc_file(cmd, env);
	i = 0;
	while (i < count)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			while (i--)
				wait(NULL);
			error_fork();
		}
		if (pid[i] == 0)
			proccess(cmd, pipe[])
	}
}

// 가장 처음의 프로세스는 1번 파이프로 쓰고, 가장 나중 파이프는 총 pid 개수 + 1번 파이프를 읽는다.
// 중간 프로세스는 2n -1 번 파이프를 읽고 2n + 1번 파이프로 쓴다 n은 자기 자신의 pid 번호
// 안쓰는 파이프는 모두 close 해주기.
// 리다이렉션은 파이프보다 우선한다.
// pipe를 먼저 dup를 해준 다음
// 리다이렉션이 있으면 dup로 덮어쓴다.