/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:23:55 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/08 17:40:28 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "minishell.h"
# include <unistd.h>

typedef struct s_process
{
	t_cmd	*cmd;
	t_env	*env;
	int		count;
}	t_process;

int		cmd_count(t_cmd *cmd);
void	close_pipe(int *fd, int process_count, int read_fd, int write_fd);
void	open_file(t_cmd *cmd, int *read_fd, int *write_fd);
int		wait_process(int count, pid_t *pid);
void	here_doc_file(t_cmd *cmd, t_env *env);
void	execute_process(t_process *process, int read_fd, int write_fd);
int		execute_parent_process(t_process *process, int read_fd, int write_fd);
int		create_process(t_cmd *cmd, t_env *env);
char	*get_command(char *cmd, t_env *env);

#endif