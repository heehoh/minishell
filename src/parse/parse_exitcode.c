/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exitcode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:05:04 by migo              #+#    #+#             */
/*   Updated: 2023/03/06 17:11:08 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int g_status = 100;

static void	fill_nbr(char *nbr, int n, size_t len)
{
	nbr[len] = '\0';
	if (n < 0)
	{
		nbr[0] = '-';
		nbr[--len] = -(n % 10) + '0';
		n = -(n / 10);
	}
	else if (n == 0)
		nbr[0] = '0';
	while (n)
	{
		nbr[--len] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		nb;
	size_t	len;

	nb = n;
	len = 0;
	if (nb <= 0)
		++len;
	while (nb)
	{
		nb /= 10;
		++len;
	}
	nbr = (char *)malloc(len + 1);
	if (nbr == 0)
		return (0);
	fill_nbr(nbr, n, len);
	return (nbr);
}

int	cnt_exit(char *str, char *exit_code)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*str)
	{
		flag_quote(str, &quote_flag);
		if (*str == '$' && quote_flag != 1)
		{
			if (str[1] == '?')
				count += ft_strlen(exit_code);
				str += 2;
		}
		str++;
		count++;
	}
	return (count);
}

void	insert_exit(char *pre, char *str, char *exit_code)
{
	int	quote_flag;
	int	count;
	int i;

	quote_flag = 0;
	count = 0;
	while (*pre)
	{
		flag_quote(pre, &quote_flag);
		if (*pre == '$' && quote_flag != 1 && pre[1] == '?')
		{
			i = -1;
			while (exit_code[++i])
			{
				printf("%c %d\n", exit_code[i], count);
				str[count] = exit_code[i];
				count++;
			}
			pre += 2;
			continue ;
		}
		str[count] = *pre;
		pre++;
		count++;
	}
}

void	replace_exit(char **str)
{
	char	*prev;
	int		count;
	char	*exit_code;

	prev = *str;
	exit_code = ft_itoa(g_status);
	count = cnt_exit(*str, exit_code);
	*str = malloc(sizeof(char) * (count + 1));
	if (*str == NULL)
		return ;
	(*str)[count] = '\0';
	insert_exit(prev, *str, exit_code);
	free(prev);
	free(exit_code);
}

void	consider_exit(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = -1;
		while (cmd->option[++i])
			replace_exit(&(cmd->option[i]));
		i = -1;
		while (cmd->file[++i].name)
			replace_exit(&(cmd->file[i].name));
		cmd = cmd->next;
	}
}