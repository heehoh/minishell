/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:23:55 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/28 15:13:19 by hujeong          ###   ########.fr       */
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
int		open_file(t_cmd *cmd, int *read_fd, int *write_fd);
int		wait_process(int count, pid_t *pid);
int		here_doc_fork(t_cmd *cmd, t_env *env);
void	execute_process(t_process *process, int read_fd,
			int write_fd, t_current *current);
int		execute_parent_process(t_process *process,
			int read_fd, int write_fd, t_current *current);
int		create_process(t_cmd *cmd, t_env *env, t_current *current);
char	*get_command(char *cmd, t_env *env);

int		is_builtin(char *command);
int		builtin_process(t_process *process, t_current *current, int write_fd);
int		builtin_cd(t_cmd *cmd, t_env *tmp, t_current *current);
int		builtin_echo(t_cmd *cmd, int write_fd);
int		builtin_env(t_cmd *cmd, t_env *tmp, int write_fd);
void	builtin_exit(t_cmd *cmd, int count, t_env *env, t_current *current);
int		builtin_export(t_process *process, int i, int j, int write_fd);
int		builtin_pwd(t_current *current, int write_fd);
int		builtin_unset(t_process *process, int i, int j, t_current *current);

#endif