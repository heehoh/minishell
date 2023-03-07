/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:56:01 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/07 19:27:33 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../libft/libft.h"
#include "../minishell.h"
#include "../error.h"

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	syntax_quote_error(int quote)
{
	write(2, "> ", 2);
	if (quote == 1)
		write(2, SYNSING, ft_strlen(SYNSING));
	else
		write(2, SYNDOUB, ft_strlen(SYNDOUB));
	write(2, SYNEND, ft_strlen(SYNEND));
	return (258);
}

int	syntax_redir_error(char *input)
{
	if (*input == '\0')
		write(2, SYNNEWL, ft_strlen(SYNNEWL));
	else if (*input == '<')
	{
		if (input[1] == '<')
			write(2, SYNHERD, ft_strlen(SYNHERD));
		else
			write(2, SYNIN, ft_strlen(SYNIN));
	}
	else if (*input == '>')
	{
		if (input[1] == '>')
			write(2, SYNAPP, ft_strlen(SYNAPP));
		else
			write(2, SYNOUT, ft_strlen(SYNOUT));
	}
	return (1);
}

int	syntax_error_util(char **input, char token, int cmd_flag)
{
	if (**input == '|')
	{
		++(*input);
		while ((**input == ' ' || is_redir(**input)))
			++(*input);
		if (cmd_flag == 0)
			return (write(2, SYNPIP, ft_strlen(SYNPIP)));
		else if (**input == '\0' && cmd_flag == 1)
		{
			write(2, "> ", 2);
			return (write(2, SYNEND, ft_strlen(SYNEND)));
		}
	}
	else
	{
		if (is_redir(*(++(*input))) && token != *((*input)++))
			return (syntax_redir_error(*input));
		while (**input == ' ')
			++(*input);
		if (**input == '|')
			return (write(2, SYNPIP, ft_strlen(SYNPIP)));
		if (**input == '\0' || is_redir(**input))
			return (syntax_redir_error(*input));
	}
	return (0);
}

int	syntax_error(char *input)
{
	int		quote_flag;
	int		cmd_flag;

	quote_flag = 0;
	cmd_flag = 0;
	while (*input)
	{
		while (*input == ' ')
			++input;
		flag_quote(input, &quote_flag);
		if (quote_flag == 0 && (is_redir(*input) || *input == '|'))
		{
			if (syntax_error_util(&input, *input, cmd_flag))
				return (258);
			cmd_flag = 0;
		}
		else
		{
			cmd_flag = 1;
			++input;
		}
	}
	if (quote_flag != 0)
		return (syntax_quote_error(quote_flag));
	return (0);
}

// 싱글쿼트나 더블쿼트가 홀수 일  때  에러
// PIPE는 앞에 명령어가 없으면 pipe token error
// pipe |  -> x unexpecter end of file
// pipe 사이에 아무문자가 없거나 공백만 있으면 에러
// < 파이프가 나올 때 또는 리다이렉션이 있을 때 까지 아무 문자가 없거나 공백일 때 에러
// syntax_error exitcode 258