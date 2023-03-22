/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:16:29 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/22 10:38:28 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <termios.h>
#include "../minishell.h"

/*ctrl c exit code 1*/
void	handler(int signum, siginfo_t *info, void )
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(t_current *current)
{
	current->new_act.__sigaction_u.__sa_sigaction = action;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
