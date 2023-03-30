/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:18:52 by migo              #+#    #+#             */
/*   Updated: 2023/03/30 12:49:58 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../minishell.h"

void	set_terminal_print_on(void);
void	exit_minishell(t_env *env, t_current *current, int num);

void	not_num(char *str, t_cmd *cmd, t_env *env, t_current *current)
{
	write(2, "minishell: exit: ", 17);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	cmd_clear(cmd);
	exit_minishell(env, current, 255);
}

void	builtin_exit(t_cmd *cmd, int count, t_env *env, t_current *current)
{
	long long	num;

	if (count == 1)
		write(1, "exit\n", 5);
	if (cmd->option[1] == NULL)
		exit(g_status);
	num = ft_atoll(cmd->option[1]);
	if (num > 2147483647 || num < -2147483648)
		not_num(cmd->option[1], cmd, env, current);
	if (cmd->option[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	cmd_clear(cmd);
	exit_minishell(env, current, num);
}
