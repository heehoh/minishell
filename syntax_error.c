/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:56:01 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/02 17:36:18 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./src/libft/libft.h"

int	flag_quote(char *sep_pipe, int *quote_flag)
{
	int	prev_quote_flag;

	prev_quote_flag = *quote_flag;
	if (*sep_pipe == '\'')
	{
		if (*quote_flag == 0)
			*quote_flag = 1;
		else if (*quote_flag == 1)
			*quote_flag = 0;
	}
	else if (*sep_pipe == '\"')
	{
		if (*quote_flag == 0)
			*quote_flag = 2;
		else if (*quote_flag == 2)
			*quote_flag = 0;
	}
	if (prev_quote_flag != *quote_flag)
		return (1);
	return (0);
}

int	syntax_error(char *input)
{
	int		quote_flag;
	int		error_flag;
	char	redir_token;

	quote_flag = 0;
	error_flag = 0;
	while (*input)
	{
		flag_quote(input, &quote_flag);
		if (quote_flag == 0
			&& (*input == '|' || *input == '<' || *input == '>'))
		{

		}
		else if (quote_flag == 0 && ft_isalnum(*input) == 0)
		{

		}
		++input;
	}
	if (quote_flag != 0)
		return(quote_error(quote_flag));
	return (0);
}

// 싱글쿼트나 더블쿼트가 홀수 일  때  에러
// pipe 사이에 아무문자가 없거나 공백만 있으면 에러
// < 파이프가 나올 때 또는 리다이렉션이 있을 때 까지 아무 문자가 없거나 공백일 때 에러
// syntax_error exitcode 258