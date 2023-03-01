/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:22:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/01 18:18:34 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// 가장 처음의 프로세스는 1번 파이프로 쓰고, 가장 나중 파이프는 총 pid 개수 + 1번 파이프를 읽는다.
// 중간 프로세스는 2n -1 번 파이프를 읽고 2n + 1번 파이프로 쓴다 n은 자기 자신의 pid 번호
// 안쓰는 파이프는 모두 close 해주기.
// 리다이렉션은 파이프보다 우선한다.
// pipe를 먼저 dup를 해준 다음
// 리다이렉션이 있으면 dup로 덮어쓴다.

int	open_read_file(t_cmd *cmd)
{
	int	read_fd;
	int	i;

	i = 0;
	while (cmd->file[i].redirection)
	{
		if (cmd->file[i].redirection == 1)
			read_fd = heardoc(cmd->file[i].file);
		else if (cmd->file[i].redirection == 2)
			read_fd = open(cmd->file[i].file, O_RDONLY);// 에러메세지 띄우기
		++i;
	}
}

int	open_write_file(t_cmd *cmd)
{
	int	write_fd;
}

void	cmd_process(t_cmd *cmd, pid_t *pid, int *pipe, int count)
{

}

void	open_pipe(int *pipe)
{

}

void	excution(t_cmd *cmd)
{
	pid_t	*pid;
	int		*pipe;
	int		count;

	count = cmd_count(cmd);
	pid = (pid_t *)malloc(sizeof(pid_t) * count);
	if (count > 0)
	{
		pipe = (int *)malloc(sizeof(int) * (count - 1) * 2);
		open_pipe(pipe);
	}
	cmd_process(cmd, pid, pipe, count);
	wait_process(count);
}
