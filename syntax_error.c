/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:56:01 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/02 19:30:53 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./src/libft/libft.h"

int	syntax_quote_error(int quote)
{
	if (quote == 1)
		write(2,
			"> minishell: unexpected EOF while looking for matching `''\n", 59);
	else
		write(2,
			"> minishell: unexpected EOF while looking for matching `\"'\n", 59);
	write(2, "minishell: syntax error: unexpected end of file\n", 43);
	return (1);
}

int	syntax_redir_error(char *input)
{
	if (*input == '\0')
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 56);
	else if (*input == '<')
	{
		if (input[1] == '<')
			write(2,
				"minishell: syntax error near unexpected token `<<'\n", 51);
		else
			write(2,
				"minishell: syntax error near unexpected token `<'\n", 50);
	}
	else
	{
		if (input[1] == '>')
			write(2,
				"minishell: syntax error near unexpected token `>>'\n", 51);
		else
			write(2,
				"minishell: syntax error near unexpected token `>'\n", 50);
	}
	return (1);
}

int	syntax_pipe_error(void)
{
	write(2,
		"minishell: syntax error near unexpected token `|'\n", 45);
	return (1);
}

int	syntax_pipe_redir_error(char **input, int redir_token)
{
	char	redir_token;

	if (**input == '|')
	{
		++(*input);
		while (**input == ' ' || **input == '<' || **input == '>')
			++(*input);
		if (*input == '\0')
			return (syntax_pipe_error());
	}
	else if (**input == '<' || **input == '>')
	{
		redir_token = **input;
		if ((*input)[1] == '<' || (*input)[1] == '>')
			++(*input);
		if (redir_token != **input)
			return (syntax_redir_error(*input));
		while (**input == ' ')
			++(*input);
		if (**input == '|' || **input == '<' || **input == '>')
			return (syntax_redir_error(*input));
		if (**input == '\0')
			return (syntax_redir_error(*input));
	}
	return (0);
}

int	syntax_error(char *input)
{
	int		quote_flag;

	quote_flag = 0;
	while (*input)
	{
		flag_quote(input, &quote_flag);
		if (quote_flag == 0)
			if (syntax_pipe_redir_error(&input, 0))
				return (1);
		++input;
	}
	if (quote_flag != 0)
		return (syntax_quote_error(quote_flag));
	return (0);
}

// 싱글쿼트나 더블쿼트가 홀수 일  때  에러
// pipe 사이에 아무문자가 없거나 공백만 있으면 에러
// < 파이프가 나올 때 또는 리다이렉션이 있을 때 까지 아무 문자가 없거나 공백일 때 에러
// syntax_error exitcode 258