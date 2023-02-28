/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:56:01 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/28 17:11:31 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

typedef struct s_syntax
{
	int	sin_quote;
	int	dou_qoute;
	int	pipe;
	int	redirection;
}	t_syntax;

void	flag_init(t_syntax *flag)
{
	flag->sin_quote = 1;
	flag->dou_qoute = 1;
	flag->pipe = 1;
	flag->redirection = 1;
}

int	syntax_redirect_error(char input, t_syntax *flag)
{
	if ()
}

int	syntax_error(char *input)
{
	t_syntax	flag;

	flag_init(&flag);
	while (*input)
	{
		if (*input == '\'' && flag.dou_qoute == 1)
			flag.sin_quote *= -1;
		else if (*input == '\"' && flag.sin_quote == 1)
			flag.dou_qoute *= -1;
		if (flag.sin_quote == flag.dou_qoute)
		{
			if (syntax_redirect_error(*input, &flag))
				break ;
		}
		++input;
	}
	if (flag.sin_quote == -1 || flag.dou_qoute == -1
		|| flag.pipe == -1 || flag.redirection == -1)
		return (print_syntax_error());
	return (0);
}

// 싱글쿼트나 더블쿼트가 홀수 일  때  에러
// pipe 사이에 아무문자가 없거나 공백만 있으면 에러
// < 파이프가 나올 때 또는 리다이렉션이 있을 때 까지 아무 문자가 없거나 공백일 때 에러