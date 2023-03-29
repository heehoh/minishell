/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:16:29 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/29 15:14:28 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <termios.h>
#include <stdlib.h>
#include "../minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_terminal_print_on(void)
{
	struct termios	terminal;

	tcgetattr(1, &terminal);
	terminal.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &terminal);
}

void	set_terminal_print_off(void)
{
	struct termios	terminal;

	tcgetattr(1, &terminal);
	terminal.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &terminal);
}

void	set_signal(void)
{
	set_terminal_print_off();
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
